<?php
	function getDOMHtml($html, $tagType, $tag) {
		// LoadHTML() checks html against TRANSITIONAL dtd, which has no HTML5 elements. This suppresses the warnings
		libxml_use_internal_errors(true);	
		$dom = new DOMDocument;
		$dom->loadHTML($html);
		// Enable TRANSITIONAL dtd checking again
		libxml_use_internal_errors(false);
		
		$domHtml = '';
		// For all DOM nodes
		foreach ($dom->getElementsByTagName('*') as $node) {
			if ($tagType == 'id') {
				if ($node->getAttribute('id') == $tag) {
					// Get raw node HTML
					$domHtml .= $dom->saveHtml($node);
				}			
			} else if ($tagType == 'class') {
				if ($node->getAttribute('class') == $tag) {
					$domHtml .= $dom->saveHtml($node);
				}
			}
		}
		
		return $domHtml;
	}
?>