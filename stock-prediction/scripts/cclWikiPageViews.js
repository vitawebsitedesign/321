$(document).ready(function() {
	$.ajax({
		url: 'scripts/cclWikiPageViews.php',
		type: 'post',
		success: function(wikiSearchVolGraph) {
			alert(wikiSearchVolGraph);
			$(wikiSearchVolGraph).appendTo('#wikiSearchVol');	
		}
	});
});