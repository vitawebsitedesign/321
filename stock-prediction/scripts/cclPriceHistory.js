$(document).ready(function() {
	$.ajax({
		url: 'scripts/cclAsxHtml.php',
		type: 'post',
		success: function(priceHistoryHtml) {
			$(priceHistoryHtml).appendTo('#priceHistoryTables');	
		}
	});
});