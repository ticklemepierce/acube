// GACube - A Graphical frontend to ACube
// 
// Copyright (C) 2007 Ryan Heise

var U=0,D=1,L=2,R=3,F=4,B=5;
var edgeFaces = [[U,F],[U,R],[U,B],[U,L],[D,F],[D,R],[D,B],[D,L],[F,R],[F,L],[B,R],[B,L]];
var cornerFaces = [[U,F,R],[U,R,B],[U,B,L],[U,L,F],[D,R,F],[D,F,L],[D,L,B],[D,B,R]];
var edgeNames = ['UF','UR','UB','UL','DF','DR','DB','DL','FR','FL','BR','BL'];
var cornerNames = ['UFR','URB','UBL','ULF','DRF','DFL','DLB','DBR'];

const PIECE_WIDTH = 40;

function Piece(oris, ori, pos) {
	this.oris = oris;
	this.ori = ori;
	this.homePos = pos;

	this.twist = function(d) { this.ori = (this.ori + d + this.oris) % oris; }
	this.toString = function() {
		var oriStr;
		if (this.ori == -1) oriStr = '@';
		else if (this.ori == 0) oriStr = '';
		else if (this.ori == this.oris - 1) oriStr = '-';
		else oriStr = '+';

		var names = this.oris == 2 ? edgeNames : cornerNames;
		var posStr = (this.homePos == -1) ? '?' : names[this.homePos];

		return oriStr+posStr;
	}
}

function Cube() {
	this.edges = new Array();
	this.corners = new Array();

	this.reset = function() {
		for (var pos = 0; pos < 12; pos++) this.edges[pos] = new Piece(2, 0, pos);
		for (var pos = 0; pos < 8; pos++) this.corners[pos] = new Piece(3, 0, pos);
	}
	this.swapEdges = function(p1, p2) { this.swapArray(this.edges, p1, p2); }
	this.swapCorners = function(p1, p2) { this.swapArray(this.corners, p1, p2); }
	this.swap = function(oris, p1, p2) { if (oris == 2) this.swapEdges(p1, p2); else this.swapCorners(p1, p2); }
	this.swapArray = function(pieces, p1, p2) { var tmp = pieces[p1]; pieces[p1] = pieces[p2]; pieces[p2] = tmp; }
	this.getEdgeFace = function(pos, side) { return this.getFace(this.edges, edgeFaces, pos, side); }
	this.getCornerFace = function(pos, side) { return this.getFace(this.corners, cornerFaces, pos, side); }
	this.getFace = function(pieces, faces, pos, side) {
		var oris = 24 / pieces.length;
		var piece = pieces[pos];
		var homePos = piece.homePos;
		var ori = piece.ori;
		if (homePos == -1) return -1;
		var dir;
		for (dir = 0; dir < oris; dir++) if (faces[pos][dir] == side) break;
		if (dir == oris) throw("Could not find side "+side+" in "+oris+" faces array: " + faces[pos]);
		return faces[homePos][(dir+(ori==-1?0:ori))%oris];
	}
	this.dump = function() { return this.edges.join(' ') + ' ' + this.corners.join(' '); }

	this.reset();
}

function FaceletView(id, oris, pos, side) {
	this.id = id;
	this.oris = oris;
	this.pos = pos;
	this.side = side;
	this.selected = false;

	this.select = function() { this.selected = true; this.update(); }
	this.deselect = function() { this.selected = false; this.update(); }
	this.click = function() {

		var pieces = this.oris == 2 ? cube.edges : cube.corners;
		var piece = pieces[this.pos];
		switch (mode) {
			case SWAP:
				if (selection) {
					if (selection.oris == this.oris) {
						cube.swap(this.oris, selection.pos, this.pos);
						selection.deselect();
						selection = null;
					}
				}
				else {
					selection = this;
					selection.select();
				}
				break;
			case TWIST:
				piece.twist(1);
				break;
			case IGNORE_POS:
				piece.homePos = -1;
				selection = null;
				break;
			case IGNORE_ORI:
				piece.ori = -1;
				selection = null;
				break;
			default:
				break;
		}
		updateAll();
	}
	this.update = function() {
		var cell = document.getElementById('st'+this.id);
		var face, pieces;
		if (this.oris == 2) {
			face = cube.getEdgeFace(this.pos, this.side);
			pieces = cube.edges;
		} else {
			face = cube.getCornerFace(this.pos, this.side);
			pieces = cube.corners;
		}
		var piece = pieces[this.pos];

		cell.style.fill = face == -1 ? 'gray' : colors[face];

		var label = '';
		if (piece.ori == -1) label += '@';
		if (piece.homePos == -1) {
			if (piece.ori <= 0) ;
			else if (piece.ori == piece.oris - 1) label += '-';
			else label += '+';
			label += '?';
		}

		if (this.selected) label = '['+label+']';
		cell.innerHTML = label;
	}
}

var colors = [ 'white', 'yellow', 'orange', 'red', 'green', 'blue' ];
var SWAP=0,TWIST=1,IGNORE_POS=2,IGNORE_ORI=3;

var facelets = new Array();
var faceletCount = 0;
var cube = new Cube();
var mode = SWAP;
var selection = null;

const getPoints = (posOnFace, face) => {
	const faceOffsetMap = [
		[1, 0], // U
		[1, 2], // D
		[0, 1], // L
		[2, 1], // R
		[1, 1], // F
		[3, 1], // B
	];

	const row = Math.floor(posOnFace / 3);
	const col = posOnFace % 3;

	console.log('row', row);

	const [faceOffsetX, faceOffsetY] = faceOffsetMap[face];

	const topLeftCorner = {
		x: (faceOffsetX * 3 * PIECE_WIDTH) + (col * PIECE_WIDTH),
		y: (faceOffsetY * 3 * PIECE_WIDTH) + (row * PIECE_WIDTH),
	}

	const firstPoint = [topLeftCorner.x, topLeftCorner.y];
	const secondPoint = [topLeftCorner.x + PIECE_WIDTH, topLeftCorner.y];
	const thirdPoint = [topLeftCorner.x + PIECE_WIDTH, topLeftCorner.y + + PIECE_WIDTH];
	const fourthPoint = [topLeftCorner.x, topLeftCorner.y + + PIECE_WIDTH];

	return `${firstPoint.join(' ')} ${secondPoint.join(' ')} ${thirdPoint.join(' ')} ${fourthPoint.join(' ')}`
}

 let facePieceCounterList = [0, 0, 0, 0, 0, 0];

function st(oris, pos, side, notFacelet) {
	if (facePieceCounterList[side] > 8) {
		facePieceCounterList[side] = 0;
	}

	if (notFacelet) {
		document.write(`<polygon class="sticker" style="fill:${colors[side]}" points="${getPoints(facePieceCounterList[side], side)}"/>`);
		facePieceCounterList[side]++;
		return;
	}

	facelets[faceletCount] = new FaceletView(faceletCount, oris, pos, side);
	document.write(`<polygon id="st${faceletCount}" class="sticker" style="fill:${colors[side]}" points="${getPoints(facePieceCounterList[side], side)}" onClick="facelets[${faceletCount}].click()"/>`);

	faceletCount++;
	facePieceCounterList[side]++;
}
function co(pos, face) { st(3, pos, face); }
function ed(pos, face) { st(2, pos, face); }
function ce(face) { st(null, null, face, true) }

function updateAll() {
	var acubeDiv = document.getElementById('acubeDiv');
	acubeDiv.innerHTML = cube.dump();
	for (var i = 0; i < faceletCount; i++) {
		facelets[i].update();
	}
}

function displayCube() {
	document.write('<svg id="svg" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 500">');
	document.write('<style type="text/css">.sticker{stroke:#000;stroke-width:1px}</style>');

	co(2,U);
	ed(2,U);
	co(1,U);
	
	ed(3,U);
	ce(U);
	ed(1,U);
	
	co(3,U);
	ed(0,U);
	co(0,U);
	
	co(2,L);
	ed(3,L);
	co(3,L);
	co(3,F);
	ed(0,F);
	co(0,F);
	co(0,R);
	ed(1,R);
	co(1,R);
	co(1,B);
	ed(2,B);
	co(2,B);

	ed(11,L);
	ce(L);
	ed(9,L);
	ed(9,F);
	ce(F);
	ed(8,F);
	ed(8,R);
	ce(R);
	ed(10,R);
	ed(10,B);
	ce(B);
	ed(11,B);

	co(6,L);
	ed(7,L);
	co(5,L);
	co(5,F);
	ed(4,F);
	co(4,F);
	co(4,R);
	ed(5,R);
	co(7,R);
	co(7,B);
	ed(6,B);
	co(6,B);
	
	co(5,D);
	ed(4,D);
	co(4,D);
	ed(7,D);
	ce(D);
	ed(5,D);
	co(6,D);
	ed(6,D);
	co(7,D);
	
	document.write('</svg>');
}
