<?php
	$mysqli = new mysqli("localhost", "unicodeo_mn626", "pEn512pyW6", "unicodeo_321");
	if ($mysqli->connect_error) {
		die("Database connection failed: " . $mysqli->connect_error);
	}
?>