<?php
	/**
	 * Displays navigation links
	 * Last modification: 29/Jul/2013
	 */

	$navLinks = array(
		/* "diary.php" => "Diary",
		"flex-bison.php" => "Flex &amp; Bison",
		"project.php" => "Project",
		"xml.php" => "XML",
		"dtd.php" => "DTD",
		"xml-schema.php" => "XML Schema",
		"sql-create-table.php" => "SQL &quot;create table&quot;"
		*/
	);
	
	while ($link = current($navLinks)) {
		echo "<li><a href='" . key($navLinks) . "'>" . $link . "</a></li>";
		next($navLinks);
	}
?>	