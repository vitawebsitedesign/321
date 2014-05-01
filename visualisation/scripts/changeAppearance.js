$(document).ready(function() {
	// Initial selection for selector is "schema", so show the available customizable properties for "schema"
	$('#property > option[value!="background"]').hide();
	$('#property > option[value="font-family"]').show();	
	
	// Only allow changing background color of schema
	$("#selector").on("change", function() {
		if ($(this).val() == "body") {
			$('#property > option[value!="background"]').hide();
			$("#property").val("background");

			// Only allow changing the font family of schema
			if ($(this).val() != "association lines") {
				$('#property > option[value="font-family"]').show();
			}
		} else {
			$('#property > option[value="font-family"]').hide();
			$('#property > option[value!="background"]').show();
			$("#property").val("background");
		}
		
		// Switch between spinner, color palette and font-family dropdown
		$("#property").trigger("change");
	});

	// Switch between spinner, color palette and font-family dropdown, depending on selected property
	$("#property").on("change", function() {
		$("#color-button").hide();
		$("#spinner").hide();
		$("#text-type").hide();	
		if ($(this).val() == "background" || $(this).val() == "color") {
			$("#color-button").show();
		} else if ($(this).val() == "font-family") {
			$("#text-type").show();
		} else {
			$("#spinner").show();
		}
	});

	// Update CSS when changing spinner
	$("#spinner").on("change", function() {
		var sel = $("#selector").val();
		$(sel).css($("#property").val(), $(this).val() + "px");
	});
	
	// Update CSS when changing colors
	$("#color-button").colorPicker({
		onSelect: function(ui, c) {
			if ($("#selector").val() == "association lines" && $("#property").val() == "background") {
				ASSOC_COLOR = c;
				drawAssocs();
			} else {
				var sel = $("#selector").val();
				$(sel).css($("#property").val(), c);
			}
		}
	});
	
	// Update font families when changing fonts
	$("#text-type").on("change", function() {
		$("body").css("font-family", $(this).val());
	});
	
	// Topbar animation
	if (typeof(xmlDoc) != "undefined") {
		$("#appearanceControls").slideDown("slow");
	}
});