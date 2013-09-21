<?php
	include_once('getHtml.php');
	$cclHtml = file_get_contents('http://snapito.com/?url=http%3A%2F%2Fstats.grok.se%2Fen%2Flatest%2FCoca-Cola_Amatil&source=snapito');
	$tagType = 'id';
	$tag = '_image';
	echo getDOMHtml($cclHtml, $tagType, $tag);
?>