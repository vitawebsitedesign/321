<?php
	include_once('dbCon.php');
	
	//prepare statement	
	if (!$stmt = $mysqli->prepare("INSERT INTO diaryEntries VALUES (NULL, ?, ?, ?)")) {
		die("Error preparing statement: " . $mysqli->error);
	}
	
	//bind name and entry
	$stmt->bind_param('sss', $name, $entry, $date);
	$name = $_POST['name'];
	$entry = $_POST['entry'];
	
	//bind date
	date_default_timezone_set('Australia/Sydney');
	$date = date('Y-m-d');

	$stmt->execute();
	$mysqli->close();
?>