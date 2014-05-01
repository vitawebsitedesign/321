function drawAssocs() {
jsPlumb.ready(function() {
	// Reset schema prior to adding jsPlumb elements
	$('#schema > *[class!="row"]').remove();
	$(".class").attr("leftmiddle", "").attr("rightmiddle", "").attr("topcenter", "").attr("bottomcenter", "");

	var instance = jsPlumb.getInstance({
		// default drag options
		DragOptions : { cursor: 'pointer', zIndex:2000 },
		// the overlays to decorate each connection with.  note that the label overlay uses a function to generate the label text; in this
		// case it returns the 'labelText' member that we set on each connection in the 'init' method below.
		ConnectionOverlays : [
			[ "Label", { 
				location:0.1,
				id:"label",
				cssClass:"aLabel"
			}]
		],
		Container:"schema"
	});		

	// this is the paint style for the connecting lines..
	var connectorPaintStyle = {
		lineWidth:4,
		strokeStyle:ASSOC_COLOR,
		joinstyle:"round",
		outlineColor:"none",
		outlineWidth:0
	},
	// .. and this is the hover style. 
	connectorHoverStyle = {
		lineWidth:4,
		strokeStyle:ASSOC_COLOR,
		outlineWidth:2,
		outlineColor:"white"
	},
	endpointHoverStyle = {
		fillStyle:"#216477",
		strokeStyle:"#216477"
	},
	// the definition of source endpoints (the small blue ones)
	sourceEndpoint = {
		endpoint:"Dot",
		paintStyle:{ 
			strokeStyle:"#7AB02C",
			fillStyle:"transparent",
			radius:7,
			lineWidth:3 
		},				
		isSource:true,
		connector:[ "Flowchart", { stub:[40, 60], gap:10, cornerRadius:5, alwaysRespectStubs:true } ],								                
		connectorStyle:connectorPaintStyle,
		hoverPaintStyle:endpointHoverStyle,
		maxConnections:-1,
		connectorHoverStyle:connectorHoverStyle,
		dragOptions:{},
		overlays:[
			[ "Label", { 
				location:[0.5, 1.5], 
				cssClass:"endpointSourceLabel" 
			} ]
		]
	},		
	// the definition of target endpoints (will appear when the user drags a connection) 
	targetEndpoint = {
		endpoint:"Dot",					
		paintStyle:{ fillStyle:"#7AB02C",radius:11 },
		hoverPaintStyle:endpointHoverStyle,
		maxConnections:-1,
		dropOptions:{ hoverClass:"hover", activeClass:"active" },
		isTarget:true,			
		overlays:[
			[ "Label", { location:[0.5, -0.5], cssClass:"endpointTargetLabel" } ]
		]
	},			
	init = function(conn) {
	};

	var _addEndpoints = function(toId, sourceAnchors, targetAnchors) {
			for (var i = 0; i < sourceAnchors.length; i++) {
				var sourceUUID = toId + sourceAnchors[i];
				instance.addEndpoint(toId, sourceEndpoint, { anchor:sourceAnchors[i], uuid:sourceUUID });
			}
			for (var j = 0; j < targetAnchors.length; j++) {
				var targetUUID = toId + targetAnchors[j];
				instance.addEndpoint(toId, targetEndpoint, { anchor:targetAnchors[j], uuid:targetUUID });						
			}
		};

	// suspend drawing and initialise.
	instance.doWhileSuspended(function() {
		// listen for new connections; initialise them the same way we initialise the connections at startup.
		instance.bind("connection", function(connInfo, originalEvent) { 
			init(connInfo.connection);
		});

		// Add endpoints
		$(".class").each(function() {
			_addEndpoints($(this).attr("id"), ANCHOR_ARR, []);
		});

		// Draw generlisation associations
		$(xmlDoc).find(TAG_GEN).each(function() {
			var superclassName = $(this).children(TAG_GEN_SUPERCLASS).text();
			$superclass = null;
			$(".class-title").each(function() {
				if ($(this).text() == superclassName) {
					$superclass = $(this).parent();
				}
			});

			var qualLabel = $(this).children(TAG_GEN_LABEL).text();
			var setLabel = false;

			// Connect subclass to superclass
			$(this).find(TAG_GEN_SUBCLASS).each(function() {
				var subclassName = $(this).text();
				$subclass = null;
				$(".class-title").each(function() {
					if ($(this).text() == subclassName) {
						$subclass = $(this).parent();
						}
				});

				var overlayArr = [];
				if (!setLabel) {
					var arrow = [
						"Custom", {
							create:function(component) {
								var arrowStyle = "border-bottom: 15px solid " + ASSOC_COLOR + ";border-left: 15px solid rgba(1,1,1,0);border-top: 15px solid rgba(1,1,1,0);border-right: 15px solid rgba(1,1,1,0);height: 0;width: 0;";
								return $("<div style=\"" + arrowStyle + "\"></div>");
							},
							location:GEN_ARROW_OFFSET
						}
					];
					var label = [
						"Label", {
							label: qualLabel,
							cssClass: "qualification-label",
							location:0.9
						}
					];
					overlayArr.push(arrow);
					overlayArr.push(label);
					setLabel = true;
				}

				$subclass.attr("topcenter", "other");
				$superclass.attr("bottomcenter", "other");
				$conn = instance.connect({
					uuids:[
						$subclass.attr("id") + "TopCenter",
						$superclass.attr("id") + "BottomCenter"
					],
					overlays:overlayArr,
					editable:false
				});
			});
		});	

		// Draw associations
		$(xmlDoc).find(TAG_ASSOC).each(function() {
			$conn = instance.connect($(this).assocData());
		});

	});

	$(".label").each(function() {
		_addEndpoints($(this).attr("id"), ANCHOR_ARR, []);
	});

	// Draw association class associations
	$(xmlDoc).find(TAG_ASSOC_CLASS_NAME).each(function() {
		$curClassDOM = null;
		var className = $(this).text();
		$(".class > .class-title").each(function() {
			if ($(this).text() == className) {
				$curClassDOM = $(this).parent();
				return false;
			}
		});

		// DOM reference to association
		$assocLabel = null;
		var assoc = $(this).parent().parent().parent().children(TAG_ASSOC_LABEL).text();
		$(".label").each(function() {
			if ($(this).text() == assoc) {
				$assocLabel = $(this);
				return false;
			}
		});

		var sideFrom = classDir($curClassDOM, $assocLabel);
		var sideTo = classDir($assocLabel, $curClassDOM);

		// Qualification
		var assocClassQual = $(this).parent().children(TAG_QUAL).text();
		var assocQualLabel = null;
		if (assocClassQual) {
			var assocQualLabel = [
				[
					"Label", {
						label: assocClassQual,
						cssClass: "qualification",
						location: ASSOC_LINK_CLASS_QUAL_POS
					}
				]
			];
		}

		instance.connect({
			uuids:[
				$curClassDOM.attr("id") + sideFrom,
				$assocLabel.attr("id") + sideTo
			],
			cssClass: "assocClass",
			overlays: assocQualLabel,
			editable:false
		});
	});

	// Draw link class associations
	$.each(classArr, function(k, className) {
		if (!className.length) {	
			return true;
		}

		$curClassDOM = null;
		$(".class > .class-title").each(function() {
			if ($(this).text() == className) {
				$curClassDOM = $(this).parent();
				return false;
			}
		});
		
		if (className[0] == "!") {	// If not an association class (i.e. a class holding only link attributes)
			// DOM reference to association
			$assocLabel = null;
			$(".label").each(function() {
				if ($(this).text() == className.substr(1)) {
					$assocLabel = $(this);
					return false;
				}
			});

			var sideFrom = classDir($curClassDOM, $assocLabel);
			var sideTo = classDir($assocLabel, $curClassDOM);

			// Qualification
			var assocClassQual = $(this).parent().children(TAG_QUAL).text ();
			var assocQualLabel = null;
			if (assocClassQual) {
				var assocQualLabel = [
					[
						"Label", {
							label: assocClassQual,
							cssClass: "qualification",
							location: ASSOC_LINK_CLASS_QUAL_POS	
						}
					]
				];
			}

			$conn = instance.connect({
				uuids:[
					$curClassDOM.attr("id") + sideFrom,
					$assocLabel.attr("id") + sideTo
				],
				cssClass: "linkClass",
				editable:false,
				overlays: assocQualLabel
			});

			if (className[0] == "!") {
				$curClassDOM.children(".class-title").remove();
			}
		}
	});

	// Dotted assocation lines for assoc and link classes
	$(".assocClass, .linkClass > path").attr({
		"stroke-width": ASSOC_DOTTED_WIDTH,
		"stroke-dasharray": ASSOC_DOTTED_DASHARR
	});

	// Make all the window divs draggable	
	instance.draggable(jsPlumb.getSelector(".class"), {
		containment: "#schema"
	});

	// Hide connections on drag
	$(".class").on("mousedown", function() {
		instance.hide(this.id, true);
	}).on("mouseup", function() {
		// Allow time for endpoint respoitioning, THEN show associations
		var classId = this.id;
		setTimeout(function() {
			instance.show(classId);
		}, 0);
	});

});

	// Correct association endpoints for link classes (they will be off by this point, because their titles are removed dynamically and thus the height of the class div changes)
	refreshAssocPos();

}

function refreshAssocPos() {
	setTimeout(function() {
		$("path").trigger("mouseover");
		$("path").trigger("mouseout");
	}, ENDPT_REPOS_TIMEOUT);
}

$(document).ready(function() {
	// Redraw associations after moving a class
	$(".class").on("mousedown", function() {
		$(this).attr("prev-box-shadow", $(this).css("box-shadow"));
	}).on("mouseup", function() {
		/* 
		 * For an unknown reason, some code needs to execute before triggering
		 * Mouse events (allowing jsplumb to redraw associations).
		 * A timeout with a delay of 0 is redundant, but somehow necessary.
		 * Im safely assuming theres a timeout in the jsPlumb library, where it asynchronously
		 * Refreshes endpoint positions... taking a small amount of time.
		 */
		refreshAssocPos();		
		$(this).css("box-shadow", $(this).attr("prev-box-shadow"));
	});
});

setTimeout(function() {
	drawAssocs();
}, ENDPT_REPOS_TIMEOUT);