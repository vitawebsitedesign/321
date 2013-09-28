<?php
	$urlArr = array ('description.php', 'requirements.php', 'userDocumentation.php', 'team.php', 'diaries.php', 'designDocumentation.php');
	$titleArr = array ('Description', 'Requirements', 'User documentation', 'Team', 'Diaries', 'Design documentation');
	
	foreach ($urlArr as $urlArrKey => $linkURL) {
		// Begin dropdown-menu
		if ($urlArrKey == 3) {
			echo '<li class="dropdown"><a href="#" class="dropdown-toggle" data-toggle="dropdown">Behind the scenes <b class="caret"></b></a><ul class="dropdown-menu">';
		}
		
		$linkHTML = '<li><a href="' . $linkURL . '">' . $titleArr[$urlArrKey] . '</a></li>';
		echo $linkHTML;
	}
	
	// End dropdown-menu
	echo '</ul></li>';
?>