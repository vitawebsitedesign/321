$(document).ready(function() {
	// if not settings element in xml then
	if (!$(xmlDoc).find("settings").length) {
		// dont continue
		return false;
	}
	
	// set css property of classes to absolute
	$(".class").css("position", "absolute");
	
	// foreach settings.class
	$(xmlDoc).find("settings").children("class").each(function() {
		// get DOM reference using "name" element
		$classDOM = null;
		var className = $(this).children("name").text();
		$(".class-title").each(function() {
			if ($(this).text() == className) {
				$classDOM = $(this).parent();
				return false;
			}
		});
		
		// explode "position" element
		var posText = $(this).children("position").text();
		var posArr = posText.split(",");
		// set css property "top" and "left" to [0] and [1] respectively 
		$classDOM.css({
			"top": posArr[0],
			"left": posArr[1]
		});
	});

	// foreach settings.css
	$(xmlDoc).find("settings").children("css").each(function() {
		// set local variable "selector" to selector
		var sel = $(this).children("selector").text();
		// if selector = "association line" then
		if (sel == "association line") {
			// set ASSOC_COLOR = value
			ASSOC_COLOR = $(this).children("value").text();
		} else {
			// while next sibling doesnt return empty empty array
			$(this).children("property").each(function() {
				// set property to current element
				var prop = $(this).text();
				// set value to subsequent element
				var val = $(this).next().text();
				// call $(selector).css(property, value)
				$(sel).css(prop, val);
			});
		}
	});
});