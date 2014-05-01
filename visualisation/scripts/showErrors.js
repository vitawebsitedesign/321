var errorsShown = false;

$(document).ready(function() {
	/*
	 * Glow animation for error messages on schema
	 */
	$.fn.errMsgAnim = function() {
		$.fn.glow = function() {
			var origCol = $(this).css("background");
			$(this).animate({
				"background-color": ERR_GLOW_COL
			}, ERR_ANIM_DUR, function() {
				$(this).glowReturn(origCol);	
			});
		}

		$.fn.glowReturn = function(origCol) {
			$(this).animate({
				"background-color": origCol
			}, ERR_ANIM_DUR, function() {
				$(this).glow();	
			});
		}

		$(this).slideDown("slow", function() {
			$(this).glow();
		});
	}

	/*
	 * Displays errors next to classes on schema
	 */
	var showErrsOnSchema = function() {
		var classWidth = $($(".class")[0]).css("width");
		var classPadding = $($(".class")[0]).css("padding");
		var classWidthTotal = parseInt(classWidth) + (parseInt(classPadding) * 2);		
		
		// For each error in error messages file
		if (typeof errMsgs === "undefined" || !errMsgs.length) return;
		errMsgs.forEach(function(err) {
			// Get DOM reference to class with error
			$classDOM = null;
			$(".class-title").each(function() {
				if ($(this).text() == err.class) {
					$classDOM = $(this).parent();
					return false;
				}
			});
		
			// Show error on schema
			$err = $("<li/>", {
				"text": err.msg			
			}).appendTo($("#error-message-sidepane > ul"));
		});		
		
		$("#errors-button").on("click", function() {
			if (!errorsShown) {
				errorsShown = true;
				$("path").css("display", "none")	;	// Hide connections when scaling
				$("#schema").animate({"font-size": ERRORS_PANE_SCHEMA_FONT_SIZE}, {queue:false});
				$("#schema").animate({"width": ERRORS_PANE_SCHEMA_SIZE}, function (){
					setTimeout(function() {
							$("path").css("display", "inline");
							$("path").trigger("mouseover");
							$("path").trigger("mouseout");
					}, ENDPT_REPOS_TIMEOUT);
					$("#error-message-sidepane").slideDown("slow");
				});
			} else {
				errorsShown = false;
				$("#error-message-sidepane").slideUp("slow", function() {
					$("path").css("display", "none")	;	// Hide connection when scaling schema
					$("#schema").animate({"font-size": "1em"}, {queue:false});
					$("#schema").animate({"width": "100%"}, function (){
						setTimeout(function() {
							$("path").css("display", "inline");							
							$("path").trigger("mouseover");
							$("path").trigger("mouseout");
						}, ENDPT_REPOS_TIMEOUT);
					});						
				});
			}
		}).errMsgAnim();
	};

	/*
	 * Displays errors in a popup inside browser window
	 */
	var showErrsOnPopup = function() {
		$("#schema").remove();

		// Append messages
		errMsgs.forEach(function(err) {
			$("<li/>", {
				text: err.msg
			}).appendTo($("#error-message-popup > ul"));
		});

		// Show messages
		$("#error-message-popup").slideDown(ERR_POPUP_ANIM_DUR);
		$("body").animate({
			"background-color": "rgb(112, 50, 50)"
		}, ERR_BG_ANIM_DUR);
	};

	if (typeof(xmlDoc) == "undefined") {
		showErrsOnPopup();
	} else {
		showErrsOnSchema();
	}
});