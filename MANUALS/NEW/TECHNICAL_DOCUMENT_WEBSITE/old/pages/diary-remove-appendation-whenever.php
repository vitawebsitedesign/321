<!DOCTYPE html>
<html>
	<head>
		<title>Individual diary</title>
		<meta charset="UTF-8">
		<meta name="description" content="CSCI321 diary">
		<meta name="keywords" content="csci321 321 diary diaries">
		<script src="http://code.jquery.com/jquery-latest.min.js"></script>
		<script src="../scripts/diary-entries.js"></script>
		<link rel="stylesheet" type="text/css" href="../styles/main.css">
	</head>
	<body>
		<header>
			<nav>
				<ul>
					<?php include_once('../scripts/fetchNav.php'); ?>
				</ul>
			</nav>
		</header>
		<h1>Individual diary</h1>
		Once a week
		<section>
			<select id="name">
				<option value="eric" selected="selected">eric</option>
				<option value="changjun">changjun</option>
				<option value="michael">michael</option>			
			</select>
			<br/>
			<textarea id="entry"></textarea>
			<br/>
			<button>ok</button>
		</section>
				
		<section id="diary-entries">
			<?php include_once('../scripts/fetchDiaryEntries.php'); ?>		
		</section>
	</body>
</html>