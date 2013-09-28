$(document).ready(function() {
	// Show only first
	$("article").hide();
	$("article:eq(0)").show();
	
	/**
	 * Display the subsequent article
	 */
	$(".next-section-div").click(function() {
		for(var articleNum = 0; articleNum < $("article").length; articleNum++) {
			var curArticle = "article:eq(" + "\"" + articleNum + "\"" + ")";
			if( $(curArticle).is(":visible")) {
				var nextArticle = "article:eq(" + "\"" + (++articleNum) + "\"" + ")";
				// Hide current, show subsequent article
				$(curArticle).hide();
				$(nextArticle).slideDown("slow");
				break;
			}
		}		
	});
});