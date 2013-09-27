$(document).ready(function() {
	// Add a diary entry via AJAX
	$('button').click(function() {
		// Show submission notification
		$("<div/>", {
			id: 'submit-ok',
			text: "added! ( ﾟヮﾟ)"
		}).insertAfter("section:eq(0)");
		
		// Hide form
		$("section:eq(0)").slideUp("slow");
		
		// Insert diary entry
		$.ajax({
			method: 'post',
			url: '../scripts/diary-entry-add.php',
			data: {
				'name': $('#name').val(),
				'entry': $('#entry').val()
			},
			success: function() {
				// Refresh entries shown
				$.ajax({
					method: 'post',
					url: '../scripts/fetchDiaryEntries.php',
					success: function(entries) {
						$('#diary-entries').html('');
						$('#diary-entries').html(entries);
						
						// Hide submission notification
						setTimeout(function() {
							$("#submit-ok").slideUp("slow");						
						}, 2000);
						
						// Highlight submitted entry
						$(".diary-entry-container").last().attr('id', 'diary-entry-container-submitted');
					}
				});
			}
		});
	});
});