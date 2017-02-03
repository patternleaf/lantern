var fs = require('fs');


// dimensions in meters
let kBottomNCubes = 6,
	kCubeWidth = 0.2857,
	kCubeMargin = .063,
	kLedOffset = (1 / 60),
	kLedsPerCube = 16;

var nCubesInRow = kBottomNCubes;
var layout = [];
var reverseOrder = false,
	topToBottom = true;

function makeRow(yOffset, nCubesInRow, reverseOrder) {
	var result = [],
		xOffset = 0;

	for (var i = 0; i < nCubesInRow; i++) {
		result = result.concat(makeCube({ x: xOffset, y: yOffset }, reverseOrder));
		xOffset += kCubeWidth + kCubeMargin;
	}
	

	if (reverseOrder) {
		result.reverse()
	}
	return result;
}

function makeCube(startPoint, reverseOrder) {
	var result = [];
	for (var i = 0; i < kLedsPerCube; i++) {
		result.push({
			point: [startPoint.x + (kLedOffset * i), startPoint.y, 0],
		});
	}

	// if (reverseOrder) {
	// 	result.reverse();
	// }
	return result;
}

var yOffset = 0;

while (nCubesInRow) {
	layout = layout.concat(makeRow(yOffset, nCubesInRow, reverseOrder));
	reverseOrder = !reverseOrder;
	yOffset += (kCubeWidth + kCubeMargin);
	nCubesInRow--;
}

if (topToBottom) {
	layout.reverse()
}

for (var i = 0; i < layout.length; i++) {
	layout[i].cubeId = Math.floor(i / kLedsPerCube);
}


fs.writeFileSync('layout.json', JSON.stringify(layout));