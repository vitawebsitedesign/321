/*
 * Calculates class positions as XML elements
 * Returns: class positions as XML elements
 */
function classPositions() {
	var classPositions = '';
	$(".class").each(function() {
		// If a valid class (not a placeholder)
		var className = $(this).children(".class-title").text();
		if (!className.length) return true;
		
		// Save class positions
		var pos = TAG_SETTINGS_CLASS + 
			TAG_SETTINGS_CLASS_NAME +
				className +
			TAG_SETTINGS_CLASS_NAME_CLOSE +
			TAG_SETTINGS_CLASS_POS +
				$(this).offset().top + "px," + $(this).offset().left + "px" +
			TAG_SETTINGS_CLASS_POS_CLOSE +
		TAG_SETTINGS_CLASS_CLOSE;
		
		classPositions += pos;
	});
	
	return classPositions;
}

/*
 * Gets customizable CSS for webpage
 * Returns: CSS for customizable elements, as XML elements
 */
function schemaCSS() {
	var css = '';
	var cssEles = {
		"sel": [
			"body",
			".qualification",
			".class",
			".attribute",
			".id",
			".label",
			".multiplicity"
		],
		"prop": [
			"background",
			"color",
			"font-size",
			"border-radius"
		]
	};
	
	// Append CSS for HTML elements
	$.each(cssEles.sel, function(k, sel) {
		var xml = TAG_SETTINGS_CSS +
			TAG_SETTINGS_SEL +
				sel +
			TAG_SETTINGS_SEL_CLOSE;
	
		$(cssEles.prop).each(function(k, prop) {
			xml += TAG_SETTINGS_PROP +
				prop +
			TAG_SETTINGS_PROP_CLOSE +
			TAG_SETTINGS_VAL + 
				$(sel).css(prop) +
			TAG_SETTINGS_VAL_CLOSE;
		});
		
		xml += TAG_SETTINGS_CSS_CLOSE;
		css += xml;
	});
	
	// JsPlumb association line color
	css += TAG_SETTINGS_CSS +
			TAG_SETTINGS_SEL +
				"association line" +
			TAG_SETTINGS_SEL_CLOSE +
			TAG_SETTINGS_PROP +
				"color" +
			TAG_SETTINGS_PROP_CLOSE +
			TAG_SETTINGS_VAL + 
				ASSOC_COLOR +
			TAG_SETTINGS_VAL_CLOSE +
		TAG_SETTINGS_CSS_CLOSE;
	
	// Font family
	var font = $("body").css("font-family");
	font = font.replace(/'/g, "").replace(/"/g, "");
	css += TAG_SETTINGS_CSS +
			TAG_SETTINGS_SEL +
				"body" +
			TAG_SETTINGS_SEL_CLOSE +
			TAG_SETTINGS_PROP +
				"font-family" +
			TAG_SETTINGS_PROP_CLOSE +
			TAG_SETTINGS_VAL + 
				font +
			TAG_SETTINGS_VAL_CLOSE +
		TAG_SETTINGS_CSS_CLOSE;

	// Schema height (since loading makes classes absolutely positoned, it will have 0 height, and thus will not "contain" the dragging properly)
	css += TAG_SETTINGS_CSS +
			TAG_SETTINGS_SEL +
				"#schema" +
			TAG_SETTINGS_SEL_CLOSE +
			TAG_SETTINGS_PROP +
				"height" +
			TAG_SETTINGS_PROP_CLOSE +
			TAG_SETTINGS_VAL + 
				$("#schema").height() + "px" +
			TAG_SETTINGS_VAL_CLOSE +
		TAG_SETTINGS_CSS_CLOSE;
	
	return css;
}

/*
 * Binds save button onto a handler that saves schema settings as XML
 */
$(document).ready(function() {
	$("#save-button").on("click", function() {
		// Append settings as xml to original schema xml
		var xmlSettings = TAG_SETTINGS + classPositions() + schemaCSS() + TAG_SETTINGS_CLOSE;
		$(xmlDoc).find("settings").remove();
		$(xmlDoc).find("project").append($(xmlSettings));
		var xmlWithSettings = (new XMLSerializer()).serializeToString(xmlDoc);	
		var xmlJs = "var xml = '" + xmlWithSettings + "';var xmlDoc = $.parseXML(xml);";
		
		// Present xml to user for copying
		$("#settings-window").children("code").text(xmlJs).parent().fadeTo("slow", 1);
	});
	
	$("#btn-settings-close").on("click", function() {
		$("#settings-window").fadeTo("slow", 0, function() {
			$(this).hide();
		});
	});
});