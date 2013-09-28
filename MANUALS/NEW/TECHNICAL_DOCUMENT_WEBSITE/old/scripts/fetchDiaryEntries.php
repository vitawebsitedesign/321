<?php
	/**
	 * Displays all diary entries
	 * Last modification: 29/Jul/2013
	 */
	include_once('dbCon.php');	 
	
	//get all diary entries
	if (!$stmt = $mysqli->prepare("SELECT * FROM diaryEntries ORDER BY id")) {
		die("Failed to prepare statement: " . $mysqli->error);		
	}
	
	$stmt->execute();
	$stmt->bind_result($id, $name, $entry, $date);

	//for each diary entry	
	while ($stmt->fetch()) {
		//echo author & contents
		echo "<div class='diary-entry-container'>" . $name . "(" . $date . "): " . stripslashes($entry) . "</div>";
	}
	
	$mysqli->close();
	

?>