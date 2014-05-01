$(document).ready(function() {
	$("#print-button").click(function() {
		$("#appearanceControls").css("display", "none");
		$(".error-message").hide();
		window.print();	
		$("#appearanceControls").css("display", "block");
		$(".error-message").show();
	});
});