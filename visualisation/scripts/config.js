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