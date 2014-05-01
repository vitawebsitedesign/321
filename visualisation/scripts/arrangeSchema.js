/*
 * Checks if a position in the schema grid is empty
 * Returns: true if the position (array index) is empty
 */
function gridPosEmpty(sortedClassArr, ind) {
	if (ind >= 0 && ind <= sortedClassArr.length - 1 && sortedClassArr[ind] == "") {
		return true;
	}
	return false;
}

/*
 * Checks if a target class (the one placing classes adject to) is on the edge of the schema
 * Returns: true if target class is on the edge
 */
function onEdge(classInd) {
	if (classInd == 0 || classInd % CLASSES_PER_ROW == 0 || (classInd + 1) % CLASSES_PER_ROW == 0) {
		return true;
	}
	return false;
}

/*
 * Arranges class when the target class is on the edge
 * Arguments: sortedClassArr = array holding newly arranged classes, className = name of class to place, connToInd = (short for "connected to index") index of target class in sortedClassArr, classInd = index of class to place in classArr
 */
function arrangeEdge(sortedClassArr, className, connToInd, classInd) {
	var pos = null, incrementAmt = null;
	var right = connToInd + 1, 
		left = connToInd - 1, 
		above = connToInd - CLASSES_PER_ROW, 
		below = connToInd + CLASSES_PER_ROW;

	// Place in best case scenarios
	if (classInd == CLASS_ARR_SIZE - 1) {						
		if (gridPosEmpty(sortedClassArr, above)) {	
			sortedClassArr[above] = className;
			return;
		} else {
			pos = left;
			incrementAmt = -1;
		}
	} else {
		if (gridPosEmpty(sortedClassArr, below)) {
			sortedClassArr[below] = className;
			return;
		} else {
			pos = right;
			incrementAmt = 1;
		}
	}
	
	if (pos == right) {
		incrementAmt = 1;
	}
	while (!gridPosEmpty(sortedClassArr, pos)) {
		pos += incrementAmt;
	}

	sortedClassArr[pos] = className;
}

/*
 * Arranges class when the target class is not on edge
 * Arguments: sortedClassArr = array holding newly arranged classes, className = name of class to place, connToInd = (short for "connected to index") index of target class in sortedClassArr
 */
function arrangeNonEdge(sortedClassArr, className, connToInd) {
	var dirArr = [connToInd + 1,		// right
		connToInd - 1, 			// left
		connToInd - CLASSES_PER_ROW, 	// above
		connToInd + CLASSES_PER_ROW 	// below
	];

	for (var dirAttempt = 0; dirAttempt < dirArr.length; dirAttempt++) {
		var dir = dirArr[dirAttempt];

		if (gridPosEmpty(sortedClassArr, dir)) {
			sortedClassArr[dir] = className;
			break;
		} else if (dirAttempt == dirArr.length - 1) {
			var pos = dirArr[0];
			while (pos < CLASS_ARR_SIZE && !gridPosEmpty(sortedClassArr, pos)) {
				// Put closest on right as possible (best case scenario)
				pos++;
			}
			if (pos == CLASS_ARR_SIZE) {
				// Put closest on left as possible (best case scenario)
				var pos = dirArr[1];
				while (pos > 0 && !gridPosEmpty(sortedClassArr, pos)) {
					pos--;
				}
			}

			sortedClassArr[pos] = className;
		}
	}
}

/*
 * Rearranges classes in the "class array" such that they are adjacent to what they're connected to
 * Arguments: mid = classArr index that represents the matrix center, classArr = array holding class names, sortedClassArr = array to-be holding class names in an order such that they appear close to eachother in the matrix
 */
function adjacentClasses(classArr, sortedClassArr, genClassArr) {
	// Store associations between classes
	var assocArr = [];
	$(xmlDoc).find(TAG_ASSOC).each(function() {
		// Get class titles from xml
		var classFromName = $(this).children(TAG_CLASS).children(TAG_CLASS_NAME).text();
		var classToName = $(this).children(TAG_OTHER_CLASS).children(TAG_CLASS_NAME).text();

		assocArr.push({
			"from": classFromName,
			"to": classToName
		});
	});

	// Store associations between link classes and labels
	$(xmlDoc).find(TAG_LINK).each(function() {
		var linkClassName = "!" + $(this).parent().children(TAG_ASSOC_LABEL).text();
		var connToClassName = $(this).parent().children(TAG_OTHER_CLASS).children(TAG_CLASS_NAME).text();
		assocArr.push({
			"from": connToClassName,
			"to": linkClassName
		});
	});

	// Store associations between association classes and labels
	$(xmlDoc).find(TAG_ASSOC_CLASS_NAME).each(function() {
		var assocClassName = $(this).text();
		var connToClassName = $(this).parent().parent().parent().children(TAG_OTHER_CLASS).children(TAG_CLASS_NAME).text();
		assocArr.push({
			"from": connToClassName,
			"to": assocClassName
		});
	});


	$.each(classArr, function(classInd, className) {
		// Dont re-arrange the class with most connections AND generlisation classes
		if (!className.length || className == sortedClassArr[mid]) {
			return true;
		}

		// Get target class
		var connToInd = null;
		$.each(assocArr, function(k, assoc) {
			if (assoc.to == className) {
				// Get index of class its connected to
				$.each(sortedClassArr, function(k, curClassName) {
					if (curClassName.length && curClassName == assoc.from) {
						connToInd = k;
						return false;
					}
				});
			}
		});

		if (onEdge(connToInd)) {
			arrangeEdge(sortedClassArr, className, connToInd, classInd);
		} else {
			arrangeNonEdge(sortedClassArr, className, connToInd);
		}
	});

	return sortedClassArr;
}

/*
 * Arranges generalisation classes such that theyre in optimal "generalisation formation" (i.e. 2 subclasses in same row, then superclass in between and above them)
 * Arguments: classArr = array holding unsorted class names, sortedClassArr = array holding sorted class names, genClasses = object holding class names involved in generalisation
 */
function arrangeGens(sortedClassArr, genClasses) {
	var posSuperclass = 1;
	var posAnchorClass = null;
	var posSubclass1 = null;
	var posSubclass2 = null;

	// For all columns, where there are spare columns on left and right of superclass column)
	for (; posSuperclass < CLASSES_PER_ROW - 1; posSuperclass++) {
		posSubclass1 = posSuperclass + CLASSES_PER_ROW - 1;
		posSubclass2 = posSuperclass + CLASSES_PER_ROW + 1;

		if (sortedClassArr[posSuperclass] == "" && sortedClassArr[posSubclass1] == "" && sortedClassArr[posSubclass2] == "") {
			break;		
		}
	}

	// Erase class in middle, if it was a generalisation class instead of a normal class
	// The result will mean that the "middle" generlisation class is just placed somewhere else, such that the generlisation formation is visually optimal
	if (sortedClassArr[mid] == genClasses.superclassName || sortedClassArr[mid] == genClasses.subclass1Name || sortedClassArr[mid] == genClasses.subclass2Name) {
		sortedClassArr[mid] = "";
	}

	sortedClassArr[posSuperclass] = genClasses.superclassName;
	sortedClassArr[posSubclass1] = genClasses.subclass1Name;
	sortedClassArr[posSubclass2] = genClasses.subclass2Name;
}



/*
 * Places classes and association classes such that they can be added 1-by-1 and the association lines wont overlap
 * Returns: sorted class array
 */
function setMidClass(classArr, numConnArr) {
	var maxConnInd = 0, maxConn = -1;
	$.each(classArr, function(k, v) {
		if (numConnArr[k] > maxConn) {
			maxConn = numConnArr[k];
			maxConnInd = k;
		}
	});

	var sortedClassArr = new Array(CLASS_ARR_SIZE);
	$.each(sortedClassArr, function(k, v) {
		sortedClassArr[k] = "";
	});

	// Put class with most connections in center of schema
	sortedClassArr[mid] = classArr[maxConnInd];
	return sortedClassArr;	
}

/*
 * Increments number of connections for a class
 * Arguments: classArr = class array, numConnArr = array holding number of connections for each class, className = target class for incrementing its connection count
 */
function incrementNumConn(classArr, numConnArr, className) {
	for (var ind = 0; ind < classArr.length - 1; ind++) {
		if (classArr[ind] == className) {		// If already in connection array
			numConnArr[ind]++;
		} else if (ind == classArr.length - 1) {	// If not stored yet
			alert('[!] arrangeSchema.js: association involves a class that doesn\'t exist');
		}
	}
}

/*
 * Constructs arranges an array of all class names, sorted by number of connections, descending
 * Returns: class array
 */
function arrangeSchema() {
	var classArr = new Array(CLASS_ARR_SIZE);
	$.each(classArr, function(k, v) {
		classArr[k] = "";
	});
	var numConnArr = [];

	var classArrInd = 0;
	$(xmlDoc).children(TAG_ROOT).children(TAG_CLASS).each(function() {
		var className = $(this).find(TAG_CLASS_NAME).text();
		classArr[classArrInd] = className;
		numConnArr[classArrInd] = 0;
		classArrInd++;
	});

	$(xmlDoc).find(TAG_LINK).children(TAG_LINK_ATTR).each(function() {
		// If has link attributes
		if ($(this).children().length) {
			var assocName = LINK_CLASS_MARKER + $(this).parent().parent().children(TAG_ASSOC_LABEL).text();
			classArr[classArrInd] = assocName;
			numConnArr[classArrInd] = 0;
			classArrInd++;
		}
	});

	// Store number of connections for each class
	$(xmlDoc).find(TAG_ASSOC).each(function() {
		// Get class titles from xml
		var classFromName = null;
		var classToName = null;

		$(this).children(TAG_CLASS).each(function() {
			if (!classFromName) {
				classFromName = $(this).children(TAG_CLASS_NAME).text();
			} else {
				classToName = $(this).children(TAG_CLASS_NAME).text();
			}
		});

		incrementNumConn(classArr, numConnArr, classFromName);
		incrementNumConn(classArr, numConnArr, classToName);
	});

	if (classArr.length) {
		// Place middle class
		var sortedClassArr = setMidClass(classArr, numConnArr);

		// Place generalisation classes in optimal positions
		var genClassArr = [];
		$(xmlDoc).find(TAG_GEN).each(function() {
			var genClasses = {
				"superclassName": $(this).children(TAG_GEN_SUPERCLASS).text(),
				"subclass1Name": $($(this).children(TAG_GEN_SUBCLASS)[0]).text(),
				"subclass2Name": $($(this).children(TAG_GEN_SUBCLASS)[1]).text()
			};

			arrangeGens(sortedClassArr, genClasses);

			// Since unsorted class array is parsed twice, erase generaisation classes from that array to prevent duplicate adds to matrix
			$(classArr).each(function(k, className) {
				if (className == genClasses.superclassName || className == genClasses.subclass1Name || className == genClasses.subclass2Name) {
					classArr[k] = "";
				}
			});

			genClassArr.push(genClasses.superclassName);
			genClassArr.push(genClasses.subclass1Name);
			genClassArr.push(genClasses.subclass2Name);
		});

		// Place non-generalisation classes
		return adjacentClasses(classArr, sortedClassArr, genClassArr);	// Place the remaining classes adjecent to whatever its connected to
	} else {
		return [];
	}
}
