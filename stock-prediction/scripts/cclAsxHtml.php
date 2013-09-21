<?php
	include_once('getHtml.php');
	$cclHtml = file_get_contents('http://www.asx.com.au/asx/research/companyInfo.do?by=asxCode&asxCode=CCL');
	$tagType = 'class';
	$tag = 'datatable';
	echo getDOMHtml($cclHtml, $tagType, $tag);
?>