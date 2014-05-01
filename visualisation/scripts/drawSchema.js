/*
 * Associations and roles are drawn inside "drawAssociations.js", as they need to be drawn using jsPlumbs "suspend" method
 */
var classArr = arrangeSchema();

// Set schema div to fixed width, so jsPlumb can correctly reposition endpoints (it doesnt reposition correctly if width is a percentage)
$("#schema").css("width", $(window).width() + "px");

// Add classes (all must be added first before adding other stuff like attributes and qualifications)
$.each(classArr, function(k, className) {
	addClass(className);	
});

$.each(classArr, function(k, className) {
	if (!className.length) return true;

	$curClassDOM = null;
	$(".class > .class-title").each(function() {
		if ($(this).text() == className) {
			$curClassDOM = $(this).parent();
			return false;
		}
	});

	$curClassXML = null;
	if (className[0] == "!") {
		// XML reference for association class attributes
		$(xmlDoc).find(TAG_ASSOC).children(TAG_ASSOC_LABEL).each(function() {
			if ($(this).text() == className.substr(1)) {
				$curClassXML = $(this).parent().children(TAG_LINK).children(TAG_LINK_ATTR);
				return false;
			}
		});

		$curClassXML.children(TAG_LINK_ATTR).each(function() {
			addAttr($(this).text(), "", $curClassDOM, "");
		});
	} else {
		$(xmlDoc).children(TAG_ROOT).children(TAG_CLASS).children(TAG_CLASS_NAME).each(function() {
			if ($(this).text() == className) {
				$curClassXML = $(this).parent();
				return false;
			}
		});

		// Attributes
		$curClassXML.children(TAG_ATTR).each(function() {
			var attrName = $(this).children(TAG_ATTR_NAME).text();
			var attrId = $(this).children(TAG_ATTR_ID).text();
			var attrMulti = $(this).children(TAG_ATTR_MULTIPLICITY).text();
			addAttr(attrName, attrMulti, $curClassDOM, attrId);
		});

		// Derived attributes
		$(xmlDoc).find(TAG_ATTR_DERIVED).each(function() {
			var attrName = "/" + $(this).children(TAG_ATTR_NAME).text();
			var attrId = $(this).children(TAG_ATTR_ID).text();
			var attrMulti = $(this).children(TAG_ATTR_MULTIPLICITY).text();
			addAttr(attrName, attrMulti, $curClassDOM, attrId);
		});

	}
});


$(document).ready(function() {
	// Update jsPlumb endpoints
	$(".class").on("click", function() {
		$("circle").trigger("mouseover");
	});

	$("#welcome").hide();
	$("#schema").animate({
		"opacity": 1
	}, "slow");
});