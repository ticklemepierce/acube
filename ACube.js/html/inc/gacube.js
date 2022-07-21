// GACube - A Graphical frontend to ACube
// 
// Copyright (C) 2007 Ryan Heise

var U=0,D=1,L=2,R=3,F=4,B=5;
var edgeFaces = [[U,F],[U,R],[U,B],[U,L],[D,F],[D,R],[D,B],[D,L],[F,R],[F,L],[B,R],[B,L]];
var cornerFaces = [[U,F,R],[U,R,B],[U,B,L],[U,L,F],[D,R,F],[D,F,L],[D,L,B],[D,B,R]];
var edgeNames = ['UF','UR','UB','UL','DF','DR','DB','DL','FR','FL','BR','BL'];
var cornerNames = ['UFR','URB','UBL','ULF','DRF','DFL','DLB','DBR'];

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

		cell.style.backgroundColor = face == -1 ? 'gray' : colors[face];

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

function st(oris, pos, side) {
	facelets[faceletCount] = new FaceletView(faceletCount, oris, pos, side);
	document.write('<td id="st'+faceletCount+'" width="40" height="40" align="center" valign="center" style="cursor: pointer; cursor: hand;" onclick="facelets['+faceletCount+'].click();"></td>');
	faceletCount++;
}
function co(pos, face) {
	 st(3, pos, face); 
}
function ed(pos, face) { st(2, pos, face); }
function ce(face) { document.write('<td width="40" height="40" bgcolor="'+colors[face]+'"></td>'); }
function bl(count) { for (var i = 0; i < count; i++) document.write('<td></td>'); }
function ro() { document.write('<tr>'); }
function rc() { document.write('</tr>'); }

function updateAll() {
	var acubeDiv = document.getElementById('acubeDiv');
	acubeDiv.innerHTML = cube.dump();
	for (var i = 0; i < faceletCount; i++) {
		facelets[i].update();
	}
}

function displayCube() {
	document.write(`
	<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.0//EN"
       "http://www.w3.org/TR/2001/REC-SVG-20050904/DTD/svg11.dtd">
<svg xmlns="http://www.w3.org/2000/svg" version="1.1" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 518 392" preserveAspectRatio="xMidYMid meet">
  <title>3x3x3</title>
  <defs>
    <g id="sticker">
        <rect x="0" y="0" width="1" height="1" stroke="black" stroke-width="0.04px" />
    </g>
  </defs>

<!--        0 1 2 3 4 5 6 7 8 9 10 11  -->
<!--        | | | | | | | | | | | |<-  -->
<!--    0 -       . . .                -->
<!--    1 -       . . .                -->
<!--    2 -       . . .                -->
<!--    3 - . . . . . . . . . . . .    -->
<!--    4 - . . . . . . . . . . . .    -->
<!--    5 - . . . . . . . . . . . .    -->
<!--    6 -       . . .                -->
<!--    7 -       . . .                -->
<!--    8 -       . . .                -->

  <g id="puzzle" transform="translate(5,5) scale(40)">
    <!-- CORNERS -->
    <use id="CORNERS-l0-o0" xlink:href="#sticker" transform="translate(5.3,2.1)" style="fill: white"/>
    <use id="CORNERS-l0-o1" xlink:href="#sticker" transform="translate(6.5,3.3)" style="fill: red"/>
    <use id="CORNERS-l0-o2" xlink:href="#sticker" transform="translate(5.3,3.3)" style="fill: limegreen"/>

    <use id="CORNERS-l1-o0" xlink:href="#sticker" transform="translate(5.3,0.1)" style="fill: white"/>
    <use id="CORNERS-l1-o1" xlink:href="#sticker" transform="translate(9.7,3.3)" style="fill: #26f"/>
    <use id="CORNERS-l1-o2" xlink:href="#sticker" transform="translate(8.5,3.3)" style="fill: red"/>

    <use id="CORNERS-l2-o0" xlink:href="#sticker" transform="translate(3.3,0.1)" style="fill: white"/>
    <use id="CORNERS-l2-o1" xlink:href="#sticker" transform="translate(0.1,3.3)" style="fill: orange"/>
    <use id="CORNERS-l2-o2" xlink:href="#sticker" transform="translate(11.7,3.3)" style="fill: #26f"/>

    <use id="CORNERS-l3-o0" xlink:href="#sticker" transform="translate(3.3,2.1)" style="fill: white"/>
    <use id="CORNERS-l3-o1" xlink:href="#sticker" transform="translate(3.3,3.3)" style="fill: limegreen"/>
    <use id="CORNERS-l3-o2" xlink:href="#sticker" transform="translate(2.1,3.3)" style="fill: orange"/>

    <use id="CORNERS-l4-o0" xlink:href="#sticker" transform="translate(5.3,6.5)" style="fill: yellow"/>
    <use id="CORNERS-l4-o1" xlink:href="#sticker" transform="translate(5.3,5.3)" style="fill: limegreen"/>
    <use id="CORNERS-l4-o2" xlink:href="#sticker" transform="translate(6.5,5.3)" style="fill: red"/>

    <use id="CORNERS-l5-o0" xlink:href="#sticker" transform="translate(3.3,6.5)" style="fill: yellow"/>
    <use id="CORNERS-l5-o1" xlink:href="#sticker" transform="translate(2.1,5.3)" style="fill: orange"/>
    <use id="CORNERS-l5-o2" xlink:href="#sticker" transform="translate(3.3,5.3)" style="fill: limegreen"/>

    <use id="CORNERS-l6-o0" xlink:href="#sticker" transform="translate(3.3,8.5)" style="fill: yellow"/>
    <use id="CORNERS-l6-o1" xlink:href="#sticker" transform="translate(11.7,5.3)" style="fill: #26f"/>
    <use id="CORNERS-l6-o2" xlink:href="#sticker" transform="translate(0.1,5.3)"  style="fill: orange"/>

    <use id="CORNERS-l7-o0" xlink:href="#sticker" transform="translate(5.3,8.5)" style="fill: yellow"/>
    <use id="CORNERS-l7-o1" xlink:href="#sticker" transform="translate(8.5,5.3)" style="fill: red"/>
    <use id="CORNERS-l7-o2" xlink:href="#sticker" transform="translate(9.7,5.3)" style="fill: #26f"/>

    <!-- EDGES -->
    <use id="EDGES-l0-o0"  xlink:href="#sticker" transform="translate(4.3,2.1)" style="fill: white"/>
    <use id="EDGES-l0-o1"  xlink:href="#sticker" transform="translate(4.3,3.3)" style="fill: limegreen"/>

    <use id="EDGES-l1-o0"  xlink:href="#sticker" transform="translate(5.3,1.1)" style="fill: white"/>
    <use id="EDGES-l1-o1"  xlink:href="#sticker" transform="translate(7.5,3.3)" style="fill: red"/>

    <use id="EDGES-l2-o0"  xlink:href="#sticker" transform="translate(4.3,0.1)" style="fill: white"/>
    <use id="EDGES-l2-o1"  xlink:href="#sticker" transform="translate(10.7,3.3)" style="fill: #26f"/>

    <use id="EDGES-l3-o0"  xlink:href="#sticker" transform="translate(3.3,1.1)" style="fill: white"/>
    <use id="EDGES-l3-o1"  xlink:href="#sticker" transform="translate(1.1,3.3)" style="fill: orange"/>

    <use id="EDGES-l4-o0"  xlink:href="#sticker" transform="translate(4.3,6.5)" style="fill: yellow"/>
    <use id="EDGES-l4-o1"  xlink:href="#sticker" transform="translate(4.3,5.3)" style="fill: limegreen"/>

    <use id="EDGES-l5-o0" xlink:href="#sticker" transform="translate(5.3,7.5)" style="fill: yellow"/>
    <use id="EDGES-l5-o1" xlink:href="#sticker" transform="translate(7.5,5.3)" style="fill: red"/>

    <use id="EDGES-l6-o0" xlink:href="#sticker" transform="translate(4.3,8.5)" style="fill: yellow"/>
    <use id="EDGES-l6-o1" xlink:href="#sticker" transform="translate(10.7,5.3)" style="fill: #26f"/>

    <use id="EDGES-l7-o0"  xlink:href="#sticker" transform="translate(3.3,7.5)" style="fill: yellow"/>
    <use id="EDGES-l7-o1"  xlink:href="#sticker" transform="translate(1.1,5.3)" style="fill: orange"/>

    <use id="EDGES-l8-o0"  xlink:href="#sticker" transform="translate(5.3,4.3)" style="fill: limegreen"/>
    <use id="EDGES-l8-o1"  xlink:href="#sticker" transform="translate(6.5,4.3)" style="fill: red"/>

    <use id="EDGES-l9-o0"  xlink:href="#sticker" transform="translate(3.3,4.3)" style="fill: limegreen"/>
    <use id="EDGES-l9-o1"  xlink:href="#sticker" transform="translate(2.1,4.3)" style="fill: orange"/>

    <use id="EDGES-l10-o0" xlink:href="#sticker" transform="translate(9.7,4.3)" style="fill: #26f"/>
    <use id="EDGES-l10-o1" xlink:href="#sticker" transform="translate(8.5,4.3)" style="fill: red"/>

    <use id="EDGES-l11-o0" xlink:href="#sticker" transform="translate(11.7,4.3)" style="fill: #26f"/>
    <use id="EDGES-l11-o1" xlink:href="#sticker" transform="translate(0.1,4.3)" style="fill: orange"/>

    <!-- CENTERS -->
    <!-- TODO: Allow the same sticker to be reused for multiple orientations -->
    <use id="CENTERS-l0-o0" xlink:href="#sticker" transform="translate(4.3,1.1)" style="fill: white"/>
    <use id="CENTERS-l0-o1" xlink:href="#sticker" transform="translate(4.3,1.1)" style="fill: white"/>
    <use id="CENTERS-l0-o2" xlink:href="#sticker" transform="translate(4.3,1.1)" style="fill: white"/>
    <use id="CENTERS-l0-o3" xlink:href="#sticker" transform="translate(4.3,1.1)" style="fill: white"/>

    <use id="CENTERS-l1-o0" xlink:href="#sticker" transform="translate(1.1,4.3)" style="fill: orange"/>
    <use id="CENTERS-l1-o1" xlink:href="#sticker" transform="translate(1.1,4.3)" style="fill: orange"/>
    <use id="CENTERS-l1-o2" xlink:href="#sticker" transform="translate(1.1,4.3)" style="fill: orange"/>
    <use id="CENTERS-l1-o3" xlink:href="#sticker" transform="translate(1.1,4.3)" style="fill: orange"/>

    <use id="CENTERS-l2-o0" xlink:href="#sticker" transform="translate(4.3,4.3)" style="fill: limegreen"/>
    <use id="CENTERS-l2-o1" xlink:href="#sticker" transform="translate(4.3,4.3)" style="fill: limegreen"/>
    <use id="CENTERS-l2-o2" xlink:href="#sticker" transform="translate(4.3,4.3)" style="fill: limegreen"/>
    <use id="CENTERS-l2-o3" xlink:href="#sticker" transform="translate(4.3,4.3)" style="fill: limegreen"/>

    <use id="CENTERS-l3-o0" xlink:href="#sticker" transform="translate(7.5,4.3)" style="fill: red"/>
    <use id="CENTERS-l3-o1" xlink:href="#sticker" transform="translate(7.5,4.3)" style="fill: red"/>
    <use id="CENTERS-l3-o2" xlink:href="#sticker" transform="translate(7.5,4.3)" style="fill: red"/>
    <use id="CENTERS-l3-o3" xlink:href="#sticker" transform="translate(7.5,4.3)" style="fill: red"/>

    <use id="CENTERS-l4-o0" xlink:href="#sticker" transform="translate(10.7,4.3)" style="fill: #26f"/>
    <use id="CENTERS-l4-o1" xlink:href="#sticker" transform="translate(10.7,4.3)" style="fill: #26f"/>
    <use id="CENTERS-l4-o2" xlink:href="#sticker" transform="translate(10.7,4.3)" style="fill: #26f"/>
    <use id="CENTERS-l4-o3" xlink:href="#sticker" transform="translate(10.7,4.3)" style="fill: #26f"/>

    <use id="CENTERS-l5-o0" xlink:href="#sticker" transform="translate(4.3,7.5)" style="fill: yellow"/>
    <use id="CENTERS-l5-o1" xlink:href="#sticker" transform="translate(4.3,7.5)" style="fill: yellow"/>
    <use id="CENTERS-l5-o2" xlink:href="#sticker" transform="translate(4.3,7.5)" style="fill: yellow"/>
    <use id="CENTERS-l5-o3" xlink:href="#sticker" transform="translate(4.3,7.5)" style="fill: yellow"/>
  </g>
</svg>`);
	// document.write('<table cellspacing="2" style="background: black; margin: 5px;">');
	// // top strip
	// ro();bl(3);co(2,U);ed(2,U);co(1,U);bl(6);rc();
	// ro();bl(3);ed(3,U);ce(U);ed(1,U);bl(6);rc();
	// ro();bl(3);co(3,U);ed(0,U);co(0,U);bl(6);rc();
	// // middle strip
	// ro();co(2,L);ed(3,L);co(3,L);co(3,F);ed(0,F);co(0,F);co(0,R);ed(1,R);co(1,R);co(1,B);ed(2,B);co(2,B);rc();
	// ro();ed(11,L);ce(L);ed(9,L);ed(9,F);ce(F);ed(8,F);ed(8,R);ce(R);ed(10,R);ed(10,B);ce(B);ed(11,B);rc();
	// ro();co(6,L);ed(7,L);co(5,L);co(5,F);ed(4,F);co(4,F);co(4,R);ed(5,R);co(7,R);co(7,B);ed(6,B);co(6,B);rc();
	// // bottom strip
	// ro();bl(3);co(5,D);ed(4,D);co(4,D);bl(6);rc();
	// ro();bl(3);ed(7,D);ce(D);ed(5,D);bl(6);rc();
	// ro();bl(3);co(6,D);ed(6,D);co(7,D);bl(6);rc();
	// document.write('</table>');
}
