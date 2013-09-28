function getClassOpenTag(id) {
	return '<div class="class" id="class' + id + '">';
}

$(document).ready(function() {
	// Parse xml
	var xml = '<people><person><name>Warren Buffet</name><age>83</age></person><house><city>Seattle</city><capacity>5</capacity></house><bank-account><balance>$5,000,000</balance></bank-account></people>';
	
	xml = $.parseXML(xml);
	$xml = $(xml);
	
	schema = '';
	var CLASS_BEGIN = '<div class="class">';
	var CLASS_END = '</div>';
	var ATT_BEGIN = '<div class="att">';
	var ATT_END = '</div>';
	
	// For each class
	var classID = -1;	// First element will have id of 0
	var numClasses = 0;
	$.each($xml.find('*'), function() {
		// Draw classes (nodes which have children), and dont include the root
		if ($(this).children().length > 0 && $(this).parents().length != 0) {
			schema += getClassOpenTag(++classID) + this.nodeName;
			
			// Draw attributes for this class
			$.each($(this).children(), function() {
				schema += ATT_BEGIN + this.nodeName + ': ' + $(this).text() + ATT_END;
			});
			
			schema += CLASS_END;
		}
		numClasses++;
	});

	// Add clases to schema
	$('#schema').append(schema);
		
	// Fancy class animations
	$('.class').on('mousedown', function() {
		$(this).animate({
			opacity:0.6
		});
	}).on('mouseup', function() {
		$(this).animate({
			opacity:1
		}, 'slow');	
	});	
		
	// Association lines	
	jsPlumb.bind('ready', function() {
		// Properties
        	var endPtProps = {
			anchor: 'AutoDefault',
                	connector: 'Flowchart',
                	endpoint: ['Dot', {radius:1}]
		}; 
		var strokeCol = '#47755c';

		jsPlumb.draggable('class0');
		jsPlumb.draggable('class1');
		jsPlumb.draggable('class2');

		// Manually position absolute elements
		var eleX = 400;
		var eleY = 20;
		$('.class').each(function() {
			$(this).css({
				left: eleX,
				top: eleY
			});
			eleX += $(this).width();
			eleY += $(this).height() * 3;
		});

		// Endpoints	     
        	var e0Toe1 = jsPlumb.addEndpoint('class0', endPtProps), 
        	e1Toe0 = jsPlumb.addEndpoint('class1', endPtProps),
        	e1Toe2 = jsPlumb.addEndpoint('class1', endPtProps),
        	e2Toe1 = jsPlumb.addEndpoint('class2', endPtProps);

		// Connections
        	jsPlumb.connect({ 
        		source:e0Toe1,
        		target:e1Toe0,
			paintStyle: {
            			strokeStyle: strokeCol,
            			lineWidth: 3
        		}
        	});
        	jsPlumb.connect({ 
        		source:e1Toe2,
        		target:e2Toe1,
        		paintStyle: {
            			strokeStyle: strokeCol,
            			lineWidth: 3
        		}
        	});        
     	});
});