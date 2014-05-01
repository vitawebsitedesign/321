// Constants to draw schema
var CLASSES_PER_ROW = 4,
	CLASS_ARR_SIZE = CLASSES_PER_ROW * CLASSES_PER_ROW,
	GRID_SPACE_CONSTANT = 200, 
	CLASS_WIDTH_CONSTANT = 39, 
	CLASS_MARGIN_CONSTANT = 23, 
	CLASS_PADDING_CONSTANT = 6, 
	CLASS_FONT_SIZE_CONSTANT = 3.6, 
	ASSOC_THICKNESS = 2, 
	ASSOC_LABEL_FONT_SIZE_MULTIPLIER = 0.2,
	ASSOC_DOTTED_WIDTH = 4,
	ASSOC_DOTTED_DASHARR = "5, 5",
	ASSOC_LINK_CLASS_QUAL_POS = 0.96,
	QUAL_OFFSET = 0.92,
	MULTIPLICITY_OFFSET = "108px",
	BASE_CLASSES_MULTIPLICITY = "multiplicity multiplicity-",
	BASE_CLASSES_ROLE = "role role-",
	GEN_ARROW_OFFSET = 0.858,
	ENDPT_REPOS_TIMEOUT = 3,
	ASSOC_COLOR = "#61B7CF",
	ERR_SHOW_TIMEOUT = 1500,
	ERR_POPUP_ANIM_DUR = 2000,
	ERR_ANIM_DUR = 3000,
	ERR_BG_ANIM_DUR = 2000,
	ERR_GLOW_COL = "red",
	ERRORS_PANE_SCHEMA_SIZE = "80%",
	ERRORS_PANE_SCHEMA_FONT_SIZE = "0.4em",
	ANCHOR_ARR = [
		"LeftMiddle",
		"TopCenter",
		"RightMiddle",
		"BottomCenter"
	];
	
// Tag identifiers to parse xml
var TAG_ROOT = "project",
	TAG_CLASS = "class",
	TAG_OTHER_CLASS = "other_class",
	TAG_CLASS_NAME = "class_name",
	TAG_ASSOC_CLASS = "association_class",
	TAG_ASSOC_CLASS_NAME = "nameOfAssociationClass",
	TAG_ATTR = "attribute",
	TAG_ATTR_DERIVED = "derived",
	TAG_ATTR_NAME = "attribute_name",
	TAG_ATTR_ID = "identifier",
	TAG_ATTR_MULTIPLICITY = "multiplicity",
	TAG_ASSOC = "association",
	TAG_ASSOC_LABEL = "nameOfAssociation",
	TAG_ASSOC_MULTIPLICITY = "multiplicity",
	TAG_QUAL = "qualification",
	TAG_QUAL_CLASS = "qualification-class",
	TAG_QUAL_NAME = "qualification-name",
	TAG_ROLE = "role",
	TAG_ROLE_CLASS = "role-class",
	TAG_ROLE_NAME = "role-name",
	TAG_GEN = "generlisation",
	TAG_GEN_SUPERCLASS = "ISA",
	TAG_GEN_SUBCLASS = "class_name",
	TAG_GEN_LABEL = "generalisation",
	TAG_MULTIPLICITY_FROM = "multiplicity-from",
	TAG_MULTIPLICITY_TO = "multiplicity-to",
	TAG_LINK = "Link",
	TAG_LINK_ATTR = "link_attribute",
	LINK_CLASS_MARKER = "!";

// Tag identifiers to save and load schema settings
var TAG_SETTINGS = "<settings>",
	TAG_SETTINGS_CLOSE = "</settings>",
	TAG_SETTINGS_CLASS = "<class>",
	TAG_SETTINGS_CLASS_CLOSE = "</class>",
	TAG_SETTINGS_CLASS_NAME = "<name>",
	TAG_SETTINGS_CLASS_NAME_CLOSE = "</name>",
	TAG_SETTINGS_CLASS_POS = "<position>",
	TAG_SETTINGS_CLASS_POS_CLOSE = "</position>",
	TAG_SETTINGS_CSS = "<css>",
	TAG_SETTINGS_CSS_CLOSE = "</css>",
	TAG_SETTINGS_SEL = "<selector>",
	TAG_SETTINGS_SEL_CLOSE = "</selector>",
	TAG_SETTINGS_PROP = "<property>",
	TAG_SETTINGS_PROP_CLOSE = "</property>",
	TAG_SETTINGS_VAL = "<value>",
	TAG_SETTINGS_VAL_CLOSE = "</value>";
	
var numClasses = 0;
// Set array index representing the matrix center
var mid = Math.ceil(CLASS_ARR_SIZE / 2) - 1;	// Minus 1 because array index starts from 0
if (CLASSES_PER_ROW % 2 == 0) {
	// Matrixes generated from "even" classes per row
	// Dont have a true center.
	// Hence, adjust mid such that its "close" the center.
	// 5 is an arbitrary number that works.
	mid -= Math.ceil(CLASSES_PER_ROW / 5);	
}

/*
 * Adds a class to the schema
 * Arguments: className = class name to add
 * Returns: class selector
 */
function addClass($className) {
	// If first class in first row, or if row is full
	if (numClasses % CLASSES_PER_ROW == 0) {
		// Create new row
		$("<div/>", {
			class: "row"
		}).appendTo("#schema");
	}

	// Append class to last row
	$class = $("<div/>", {
		class: "class",
		id: "class" + numClasses
	}).css({
		"font-size": (CLASS_FONT_SIZE_CONSTANT / CLASSES_PER_ROW) + "em",
		"margin": (CLASS_MARGIN_CONSTANT / CLASSES_PER_ROW) + "%",
		"padding": (CLASS_PADDING_CONSTANT / CLASSES_PER_ROW) + "%",
		"width": (CLASS_WIDTH_CONSTANT / CLASSES_PER_ROW) + "%",
		"opacity": (($className == "") ? 0 : 1)
	});
	$("<div/>", {
		class: "class-title",
		text: $className
	}).appendTo($class);

	$class.appendTo($(".row").last());
	numClasses++;

	return $class;
}

/*
 * Adds an attribute to a class
 * Arguments: text = attribute name, class = class to add attribute to, idNum = ID number (-1 means none)
 */
function addAttr(name, multi, $class, id) {
	$attr = $("<div/>", {
		class: "attribute",
		text: name + multi
	}).appendTo($class);

	if (id.length) {
		$("<span/>", {
			class: "id",
			text: id
		}).appendTo($attr);
	}
}

/*
 * Sets qualification position
 * Arguments: pos = position (e.g. top), class = class to add qualification to
 * Returns: class selector
 */
$.fn.setPos = function(pos, $class) {
	var offsetHor = 0, offsetVer = 0;

	if (pos == "RightMiddle") {
		offsetHor = $class.outerWidth();
		offsetVer = ($class.outerHeight() / 2) - ($(this).outerHeight() / 2);
	} else if (pos == "BottomCenter") {
		offsetHor = ($class.outerWidth() / 2) - ($(this).outerWidth() / 2);
		offsetVer = $class.outerHeight();
	} else if (pos == "LeftMiddle") {
		offsetHor = $(this).outerWidth() * -1;
		offsetVer = ($class.outerHeight() / 2) - ($(this).outerHeight() / 2);
	} else {
		offsetHor = ($class.outerWidth() / 2) - ($(this).outerWidth() / 2);
		offsetVer = $(this).outerHeight() * -1;
	}

	$(this).css({
		"left": offsetHor + "px",
		"top": offsetVer + "px"
	}).appendTo($class);

	return $(this);
}

/*
 * Adds a qualification to a class
 * Arguments: name = qualification name, class = class to add qualfiication to, pos = qualification position (e.g. top)
 */
$.fn.addQual = function($classFrom, $classTo) {
	var qualClassName = $(this).children(TAG_QUAL_CLASS).text();
	$qualClass = $classTo;
	$connClass = $classFrom;

	if ($classFrom.children('.class-title').text() == qualClassName) {
		$qualClass = $classFrom;
		$connClass = $classTo;
	}

	var side = null;
	switch (classDir($qualClass, $connClass)) {
		case "RightMiddle":
			side = "right";
			break;
		case "LeftMiddle":
			side = "left"
			break;
		case "TopCenter":
			side = "top";
			break;
		case "BottomCenter":
			side = "bottom"
			break;
		default:
			alert("Error: drawSchema.js failed to get direction to draw qualification");
	}

	var qualName = $(this).children(TAG_QUAL_NAME).text();
	$("<div/>", {
		class: "qualification",
		"font-size": (CLASS_FONT_SIZE_CONSTANT / CLASSES_PER_ROW) + "em",
		text: qualName
	}).appendTo($qualClass).setPos(side, $qualClass);
}

/*
 * Determines if 2 classes are placed on same row
 * Arguments: $src = class connecting to another class, $target = class being connected to
 * Returns: true if on same row, otherwise false
 */
function sameRow($src, $target) {
	var idSrc = $src.attr("id"), idTarget = $target.attr("id");
	var indSrc = idSrc.substr(idSrc.lastIndexOf("s") + 1), indTarget = idTarget.substr(idTarget.lastIndexOf("s") + 1);
	var rowSrc = Math.floor(indSrc / CLASSES_PER_ROW), rowTarget = Math.floor(indTarget / CLASSES_PER_ROW);
	return (rowSrc == rowTarget);
}

/*
 * Gets direction of a target class relative to a source class
 * Arguments: classFrom = class the association starts from, classTo = class the associations ends to
 * Returns: "above", "right", "left", "below"
 */
function classDir($src, $target) {
	var dir = null;
	var endPtInd = 0;

	// Special case scenario: association to itself
	if ($src.html() == $target.html()) {
		for (; endPtInd < ANCHOR_ARR.length - 1; endPtInd++) {
			curEndPt = ANCHOR_ARR[endPtInd];
			if ($src.attr(curEndPt) == "self") {
				break;
			}
		}

		// Attempt to return vacant adjacent endpt from source endpt
		var indCounterClockwise = (endPtInd + (ANCHOR_ARR.length - 1)) % ANCHOR_ARR.length;
		var indClockwise = (endPtInd + 1) % ANCHOR_ARR.length;
		var indOpp = (endPtInd + 2) % ANCHOR_ARR.length;
		var endPtCC = ANCHOR_ARR[indCounterClockwise];
		var endPtC = ANCHOR_ARR[indClockwise];
		var endPtOpp = ANCHOR_ARR[indOpp];

		if (!$src.attr(endPtCC)) {
			dir = endPtCC;
		} else if (!$src.attr(endPtC)) {
			dir = endPtC;
		} else {
			dir = endPtOpp;
		}

		$src.attr(dir, "self");
		return dir;
	}

	// Best case scenario: return endpoint such that association has minimal corners
	var diffx = $src.offset().left - $target.offset().left;
	var diffy = $src.offset().top - $target.offset().top;
	if (sameRow($src, $target)) {	// If left or right
		if (diffx < 0) {
			dir = "RightMiddle";
		} else {
			dir = "LeftMiddle";
		}
	} else {	// If above or below
		if (diffy > 0) {
			dir = "TopCenter";
		} else {
			dir = "BottomCenter";
		}
	}

	// Worst case scenario: endpoint calculated for best-case already taken, get an available endpoint
	var availEndPts = [];
	for (var endPtInd = 0; endPtInd < ANCHOR_ARR.length; endPtInd++) {
		// If taken
		if (!$src.attr(ANCHOR_ARR[endPtInd])) {
			availEndPts.push(ANCHOR_ARR[endPtInd]);
		}
	}
	if ($.inArray(dir, availEndPts) == -1) {
		dir = availEndPts[0];
	}

	$src.attr(dir, "other");
	return dir;
}

$.fn.assocData = function() {
	var classFromName = $(this).children(TAG_CLASS).children(TAG_CLASS_NAME).text();
	var classToName = $(this).children(TAG_OTHER_CLASS).children(TAG_CLASS_NAME).text();

	// Get DOM class references		
	$classFrom = null;
	$classTo = null;

	$(".class-title").each(function() {
		if ($(this).text() == classFromName) {
			$classFrom = $(this).parent();
		} else if ($(this).text() == classToName) {
			$classTo = $(this).parent();
		}
	});

	// If association to itself
	if (classFromName == classToName) {
		$classTo = $classFrom;
	}

	var sideFrom = classDir($classFrom, $classTo);
	var sideTo = classDir($classTo, $classFrom);

	var multiplicityFrom = $(this).children(TAG_CLASS).children(TAG_ASSOC_MULTIPLICITY).text();
	multiplicityFrom = multiplicityFrom.replace("[", "");
	multiplicityFrom = multiplicityFrom.replace("]", "");
	var roleFrom = $(this).children(TAG_CLASS).children(TAG_ROLE).text();
	var qualFrom = $(this).children(TAG_CLASS).children(TAG_QUAL).text();

	var multiplicityTo = $(this).children(TAG_OTHER_CLASS).children(TAG_ASSOC_MULTIPLICITY).text();
	multiplicityTo = multiplicityTo.replace("[", "");
	multiplicityTo = multiplicityTo.replace("]", "");
	var roleTo = $(this).children(TAG_OTHER_CLASS).children(TAG_ROLE).text();
	var qualTo = $(this).children(TAG_OTHER_CLASS).children(TAG_QUAL).text();

	var overlayArr = [
		["PlainArrow", {
			height: 3,
			length: 9,
			location: 0.5,
			paintStyle: ASSOC_COLOR
		}],
		["Label", {
			label: $(this).children(TAG_ASSOC_LABEL).text(), 
			cssClass: "label"
		}],
		["Label", {
			label: multiplicityFrom, 
			cssClass: BASE_CLASSES_MULTIPLICITY + sideFrom,
			location: 0.05
		}],
		["Label", {
			label: multiplicityTo, 
			cssClass: BASE_CLASSES_MULTIPLICITY + sideTo,
			location: 0.95
		}],
		["Label", {
			label: roleFrom, 
			cssClass: BASE_CLASSES_ROLE + sideFrom,
			location: 0.15
		}],
		["Label", {
			label: roleTo, 
			cssClass: BASE_CLASSES_ROLE + sideTo,
			location: 0.85
		}]
	];

	if (qualFrom) {
		var qualFromLabel = [
			"Label", {
				label: qualFrom,
				cssClass: "qualification",
				location: 1 - QUAL_OFFSET
			}
		];
		overlayArr.push(qualFromLabel);
	}
	if (qualTo) {
		var qualToLabel = [
			"Label", {
				label: qualTo,
				cssClass: "qualification",
				location: QUAL_OFFSET
			}
		];
		overlayArr.push(qualToLabel);
	}

	return {
		uuids:[
			$classFrom.attr("id") + sideFrom,
			$classTo.attr("id") + sideTo
		],
		overlays: overlayArr,
		editable:false
	};
}