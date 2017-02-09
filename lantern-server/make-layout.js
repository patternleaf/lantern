var fs = require('fs');


// dimensions in meters
var kCubeWidth = 0.2857,
	kCubeMargin = .063,
	kLedOffset = (1 / 60),
	kLedsPerCube = 16;

var layout = [];

function makeCube(startPoint, reverseOrder, cubeId, checker) {
	var result = [];
	for (var i = 0; i < kLedsPerCube; i++) {
		result.push({
			point: [startPoint.x + (kLedOffset * i), startPoint.y, 0],
			cubeId: cubeId,
			checker: checker
		});
	}

	if (reverseOrder) {
		result.reverse();
	}
	return result;
}

var cubeOrder = [
	[null, 	null, null, 	null, 	null, 	20],
	[null, 	null, null, 	null, 	19, 		18],
	[null, 	null, null, 	15, 		16, 		17],
	[null, 	null, 0, 			 6,			 7,			 8],
	[null, 	1,		2, 			11, 		10, 		 9],
	[5, 		4, 		3, 			12, 		13, 		14]
];

var ltrCubes = [1, 2, 6, 7, 8, 12, 13, 14, 15, 16, 17, 20];
var checkerCubes = [5, 1, 0, 3, 15, 11, 19, 7, 13, 20, 17, 8, 14];

var cubes = [];

for (var rowNum = 0; rowNum < cubeOrder.length; rowNum++) {
	var row = cubeOrder[rowNum];
	for (var colNum = 0; colNum < row.length; colNum++) {
		var cubeVal = row[colNum];
		if (cubeVal != null) {
			cubes.push({ 
				cubeId: cubeVal, 
				ltr: (ltrCubes.indexOf(cubeVal) == -1), 
				coordinates: { x: colNum, y: rowNum },
				checker: (checkerCubes.indexOf(cubeVal) != -1)
			});
		}
	}
}

cubes.sort(function(a, b) { return a.cubeId - b.cubeId; });

// console.log(cubes);

for (var i = 0; i < cubes.length; i++) {
	var cube = cubes[i];
	var startPoint = { 
		x: cube.coordinates.x * (kCubeWidth + kCubeMargin),
		y: cube.coordinates.y * (kCubeWidth + kCubeMargin)
	};
	layout = layout.concat(makeCube(startPoint, cube.ltr, cube.cubeId, cube.checker));
}

fs.writeFileSync('layout.json', JSON.stringify(layout));