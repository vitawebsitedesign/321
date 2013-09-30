$(document).ready(function() {
	// Enlarge canvas
	var canvas = document.getElementById('viewport');
	canvas.width = window.innerWidth * 2;
        canvas.height = window.innerHeight * 2;
	
        var sys = arbor.ParticleSystem();
        sys.renderer = Renderer("#viewport") ;
        sys.parameters({stiffness:900, repulsion:40000, gravity:true, dt:0.015, precision:1})  
          
        var TOKEN_COL = 'black';
	var FUNC_COL = 'gray';
	var XML_COL = 'red';
        var TOKEN_SHAPE = 'rectangle';
	var FUNC_SHAPE = 'rectangle';
	var XML_SHAPE = 'dot';
	
        var data = {
		nodes: {
			// Parent node
			'tcml': {'color':XML_COL, 'shape':XML_SHAPE, 'label':'tcml'},
			
			// Tokens
			'association_multiplicity': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'association_multiplicity'},
			'association_name': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'association_name'},
			'link_attribute': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'association_name'},
			'compulsory_multiplicity': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'compulsory_multiplicity'},
			'list_of_association_class_qualification': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'list_of_association_class_qualification'},
			'association_class_name': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'association_class_name'},
			'right_class_name': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'right_class_name'},
			'right_class_role': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'right_class_role'},
			'generalization': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'generalization'},
			'list_of_class': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'list_of_class'},
			'generalization_type': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'generalization_type'},
			'parentClass': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'parentClass'},
			'class_definition': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'class_definition'},
			'class_name': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'class_name'},
			'member_definition': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'member_definition'},
			'association': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'association'},
			'left_class_name': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'left_class_name'},
			'left_class_role': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'left_class_role'},
			'list_of_qualification': {'color':TOKEN_COL, 'shape':TOKEN_SHAPE, 'label':'list_of_qualification'},
			
			// Functions
			'addAssoNodeMultiplicity': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addAssoNode()', 'description':'Arguments: current class, "MULTIPLICITY", multiplicity'},
			'addAssoNodeAssociation': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addAssoNode()', 'description':'Arguments: association name, "ASSOCIATION_NAME", assication name'},
			'addAssoNodeAttribute': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addAssoNode()', 'description':'Arguments: current association name, "ATTRIBUTE", attribute name'},
			'addAssoNodeAssociationClassQualification': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addAssoNodeAssociationClassQualification()', 'description':'Arguments: "ASSOCIATION_CLASS_NAME", "ASSOCIATION_CLASS_QUALIFICATION", association class qualification name'},
			'resetAssociationClassName': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'resetAssociationClassName()', 'description':'Arguments: assication class name'},
			'addAssoNodeAssociationClass': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addAssoNode()', 'description':'Arguments: "", "ASSOCIATION_CLASS_NAME", association class name'},
			'nameExist': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'nameExist()', 'description':'Arguments: class name<br/>If the function is called from addAssoNode(), associationAttributeExist(current class name, attribute name, attribute value) will be called'},
			'associationAttributeExist': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'associationAttributeExist()', 'description':'Arguments: current class name, attribute name, attribute value'},
			'addAssoNodeClass': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addAssoNode()', 'description':'Arguments: "", "CLASS_NAME", class name'},
			'resetClassName': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'resetClassName()', 'description':'Arguments: class name'},
			'addAssoNodeRole': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addAssoNode()', 'description':'Arguments: current class name, "ROLE", role name'},
			'writeGeneralization': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeGeneralization()', 'description':'Arguments: none'},
			'addGeneralizationNodeChild': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addGeneralizationNode()', 'description':'Arguments: "CHILDREN_CLASS", child class name'},
			'addGeneralizationNodeType': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addGeneralizationNode()', 'description':'Arguments: "GENERALIZATION_TYPE", generalization name'},
			'addGeneralizationNodeParent': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addGeneralizationNode()', 'description':'Arguments: "PARENT_CLASS", name of parent class in generalization'},
			
			
			
			
			
			
			'write_classDefinition': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'write_classDefinition()', 'description':'Arguments: class name'},
			'add_name': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'add_name()', 'description':'Arguments: class name'},
			'add_node': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'add_node()', 'description':'Arguments: class name, attribute name, multiplicity, id'},
			'attributeExist': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'attributeExist()', 'description':'Arguments: class name, attribute name'},
			'write_associationDefinition': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'write_associationDefinition()', 'description':'Arguments: none'},
			'returnClassName': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'returnClassName()', 'description':'Arguments: '},
			'writeAssociationName': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeAssociationName()', 'description':'Arguments: file descriptor for "information.xml"'},
			'writeLeftMultiplicity': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeLeftMultiplicity()', 'description':'Arguments: file descriptor for "information.xml", current class name'},
			'writeLeftRole': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeLeftRole()', 'description':'Arguments: file descriptor for "information.xml", current class name'},
			'writeLeftQualification': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeLeftQualification()', 'description':'Arguments: file descriptor for "information.xml", current class name'},
			'writeRightMultiplicity': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeRightMultiplicity()', 'description':'Arguments: file descriptor for "information.xml", current class name'},
			'writeRightRole': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeRightRole()', 'description':'Arguments: file descriptor for "information.xml", current class name'},
			'writeRightQualification': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeRightQualification()', 'description':'Arguments: file descriptor for "information.xml", current class name'},
			'writeLinkAttribute': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeLinkAttribute()', 'description':'Arguments: file descriptor for "information.xml"'},
			'writeLinkAssociationClass': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'writeLinkAssociationClass()', 'description':'Arguments: file descriptor for "information.xml"'},
			'checkLinkAssociationClass': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'checkLinkAssociationClass()', 'description':'Arguments: none'},
			'checkLinkAttribute': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'checkLinkAttribute()', 'description':'Arguments: none'},
			'addAssoNodeQualification': {'color':FUNC_COL, 'shape':FUNC_SHAPE, 'label':'addAssoNode()', 'description':'Arguments: current class, "QUALIFICATION", qualification name'},
			'information.xml': {'color':XML_COL, 'shape':XML_SHAPE, 'label':'information.xml', 'description':':D'}
		},
		edges: {			
			// Edges from token nodes
			'association_multiplicity': {'addAssoNodeMultiplicity':{}},
			'association_name': {'addAssoNodeAssociation':{}},
			'link_attribute': {'addAssoNodeAttribute':{}},
			'compulsory_multiplicity': {'addAssoNodeMultiplicity':{}},
			'list_of_association_class_qualification': {'addAssoNodeAssociationClassQualification':{}},
			'association_class_name': {'resetAssociationClassName':{}, 'addAssoNodeAssociationClass':{}},
			'right_class_name': {'nameExist':{}, 'addAssoNodeClass':{}, 'resetClassName':{}},
			'right_class_role': {'addAssoNodeRole':{}},
			'generalization': {'writeGeneralization':{}},
			'list_of_class': {'addGeneralizationNodeChild':{}},
			'generalization_type': {'addGeneralizationNodeType':{}},
			'parentClass': {'addGeneralizationNodeParent':{}},
			'class_definition': {'write_classDefinition':{}},
			'class_name': {'add_name':{}},
			'member_definition': {'add_node':{}},
			'association': {'write_associationDefinition':{}},
			'left_class_name': {'nameExist':{}, 'addAssoNodeClass':{}},
			'left_class_role': {'addAssoNodeRole':{}},
			'list_of_qualification': {'addAssoNodeQualification':{}},

			// Edges from function nodes
			'addAssoNodeMultiplicity': {'nameExist':{}},
			'addAssoNodeAssociation': {'nameExist':{}},
			'addAssoNodeAttribute': {'nameExist':{}},
			'addAssoNodeMultiplicity': {'nameExist':{}},
			'addAssoNodeAssociationClassQualification': {'nameExist':{}},
			'addAssoNodeAssociationClass': {'nameExist':{}},
			'addAssoNodeClass': {'nameExist':{}},
			'writeGeneralization': {'information.xml':{}},
			
			'write_classDefinition': {'information.xml':{}},
			'add_node': {'attributeExist':{}},
			'addAssoNodeRole': {'nameExist':{}},
			'addAssoNodeQualification': {'nameExist':{}},
			'write_associationDefinition': {'returnClassName':{}, 'writeAssociationName':{}, 'writeLeftMultiplicity':{}, 'writeLeftRole':{}, 'writeLeftQualification':{}, 'writeRightMultiplicity':{}, 'writeRightRole':{}, 'writeRightQualification':{}, 'writeLinkAttribute':{}, 'writeLinkAssociationClass':{}},
			'writeLinkAttribute': {'checkLinkAttribute':{}},
			'writeLinkAssociationClass': {'checkLinkAssociationClass':{}}
		}
        };
          
        sys.graft(data);
          
	$('canvas').mousemove(function(e) {
            var pos = $(this).offset();
            var p = {x:e.pageX-pos.left, y:e.pageY-pos.top}
            selected = nearest = dragged = sys.nearest(p);
	
	    // For function nodes
            if (selected.node !== null && selected.node.data.color == FUNC_COL){
            	// Show arguments on mouseover
            	$('#description-window').html(selected.node.data.description);	
            }
        });
});