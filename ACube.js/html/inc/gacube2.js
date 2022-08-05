const PYRA_SVG = `
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.0//EN"
       "http://www.w3.org/TR/2001/REC-SVG-20050904/DTD/svg11.dtd">
<svg xmlns="http://www.w3.org/2000/svg" version="1.1" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="-20 -20 546 480" preserveAspectRatio="xMidYMid meet">
  <defs>
  </defs>
  <title>pyraminx</title>
  <defs>
    <g id="stickerA" transform="scale(1, 0.577350269)">
      <path
         d="m 0,1.732050808 1,-1.732050808 1,1.732050808 z"
         stroke="black" stroke-width="0.04px" stroke-linecap="butt" stroke-linejoin="round"
      />
    </g>
    <g id="stickerV" transform="scale(1, 0.577350269)">
      <path
         d="m 0,0 1,1.732050808 1,-1.732050808 z"
         stroke="black" stroke-width="0.04px" stroke-linecap="butt" stroke-linejoin="round"
      />
    </g>
  </defs>
<!--        0 1 2 3 4 5 6 7 8 9 10   -->
<!--        | | | | | | | | | | |    -->
<!--    0 - L L L L L F R R R R R    -->
<!--    1 -   L L L F F F R R R      -->
<!--    2 -     L F F F F F R        -->
<!--    3 -       D D D D D          -->
<!--    4 -         D D D            -->
<!--    5 -           D              -->
  <g id="puzzle" transform="translate(5, 5) scale(40, 69.28203232)">
    <!-- CORNERS -->
    <use id="CORNERS-l0-o0" xlink:href="#stickerV" transform="translate(5.2, 1.066666667)" style="fill: limegreen"/>
    <use id="CORNERS-l0-o1" xlink:href="#stickerA" transform="translate(3, 0)" style="fill: red"/>
    <use id="CORNERS-l0-o2" xlink:href="#stickerA" transform="translate(7.4, 0)" style="fill: blue"/>
    <use id="CORNERS-l3-o0" xlink:href="#stickerA" transform="translate(4.2, 3.2)" style="fill: yellow"/>
    <use id="CORNERS-l3-o1" xlink:href="#stickerA" transform="translate(2, 1)" style="fill: red"/>
    <use id="CORNERS-l3-o2" xlink:href="#stickerV" transform="translate(4.2, 2.066666667)" style="fill: limegreen"/>
    <use id="CORNERS-l2-o0" xlink:href="#stickerA" transform="translate(6.2, 3.2)" style="fill: yellow"/>
    <use id="CORNERS-l2-o1" xlink:href="#stickerV" transform="translate(6.2, 2.066666667)" style="fill: limegreen"/>
    <use id="CORNERS-l2-o2" xlink:href="#stickerA" transform="translate(8.4, 1)" style="fill: blue"/>
    <use id="CORNERS-l1-o1" xlink:href="#stickerA" transform="translate(9.4, 0)" style="fill: blue"/>
    <use id="CORNERS-l1-o2" xlink:href="#stickerA" transform="translate(1, 0)" style="fill: red"/>
    <use id="CORNERS-l1-o0" xlink:href="#stickerA" transform="translate(5.2, 4.2)" style="fill: yellow"/>
    <!-- "TIPS" -->
    <!-- CORNERS2 -->
    <use id="CORNERS2-l0-o0" xlink:href="#stickerA" transform="translate(5.2, 0.066666667)" style="fill: limegreen"/>
    <use id="CORNERS2-l0-o1" xlink:href="#stickerV" transform="translate(4, 0)" style="fill: red"/>
    <use id="CORNERS2-l0-o2" xlink:href="#stickerV" transform="translate(6.4, 0)" style="fill: blue"/>
    <use id="CORNERS2-l3-o0" xlink:href="#stickerV" transform="translate(3.2, 3.2)" style="fill: yellow"/>
    <use id="CORNERS2-l3-o1" xlink:href="#stickerV" transform="translate(2, 2)" style="fill: red"/>
    <use id="CORNERS2-l3-o2" xlink:href="#stickerA" transform="translate(3.2, 2.066666667)" style="fill: limegreen"/>
    <use id="CORNERS2-l2-o0" xlink:href="#stickerV" transform="translate(7.2, 3.2)" style="fill: yellow"/>
    <use id="CORNERS2-l2-o1" xlink:href="#stickerA" transform="translate(7.2, 2.066666667)" style="fill: limegreen"/>
    <use id="CORNERS2-l2-o2" xlink:href="#stickerV" transform="translate(8.4, 2)" style="fill: blue"/>
    <use id="CORNERS2-l1-o1" xlink:href="#stickerV" transform="translate(10.4,0)" style="fill: blue"/>
    <use id="CORNERS2-l1-o2" xlink:href="#stickerV" transform="translate(0, 0)" style="fill: red"/>
    <use id="CORNERS2-l1-o0" xlink:href="#stickerV" transform="translate(5.2, 5.2)" style="fill: yellow"/>
    <!-- EDGES -->
    <use id="EDGES-l0-o0" xlink:href="#stickerV" transform="translate(3, 1)" style="fill: red"/>
    <use id="EDGES-l0-o1" xlink:href="#stickerA" transform="translate(4.2, 1.066666667)" style="fill: limegreen"/>
    <use id="EDGES-l5-o0" xlink:href="#stickerA" transform="translate(6.2, 1.066666667)" style="fill: limegreen"/>
    <use id="EDGES-l5-o1" xlink:href="#stickerV" transform="translate(7.4, 1)" style="fill: blue"/>
    <use id="EDGES-l1-o0" xlink:href="#stickerV" transform="translate(8.4, 0)" style="fill: blue"/>
    <use id="EDGES-l1-o1" xlink:href="#stickerV" transform="translate(2, 0)" style="fill: red"/>
    <use id="EDGES-l2-o0" xlink:href="#stickerV" transform="translate(5.2, 3.2)" style="fill: yellow"/>
    <use id="EDGES-l2-o1" xlink:href="#stickerA" transform="translate(5.2, 2.066666667)" style="fill: limegreen"/>
    <use id="EDGES-l3-o0" xlink:href="#stickerV" transform="translate(9.4, 1)" style="fill: blue"/>
    <use id="EDGES-l3-o1" xlink:href="#stickerV" transform="translate(6.2, 4.2)" style="fill: yellow"/>
    <use id="EDGES-l4-o0" xlink:href="#stickerV" transform="translate(4.2, 4.2)" style="fill: yellow"/>
    <use id="EDGES-l4-o1" xlink:href="#stickerV" transform="translate(1, 1)" style="fill: red"/>
  </g>
</svg>
`;


const SVG = `
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
    
    <use id="CENTERS-l1-o0" xlink:href="#sticker" transform="translate(1.1,4.3)" style="fill: orange"/>

    <use id="CENTERS-l2-o0" xlink:href="#sticker" transform="translate(4.3,4.3)" style="fill: limegreen"/>
    
    <use id="CENTERS-l3-o0" xlink:href="#sticker" transform="translate(7.5,4.3)" style="fill: red"/>
    
    <use id="CENTERS-l4-o0" xlink:href="#sticker" transform="translate(10.7,4.3)" style="fill: #26f"/>
    
    <use id="CENTERS-l5-o0" xlink:href="#sticker" transform="translate(4.3,7.5)" style="fill: yellow"/>
  </g>
</svg>`;

const reorder = function(arr, index){
  const start = arr.slice(index);
  const end = arr.slice(0,index);
  return start.concat(end);
}


let SWAP=0,TWIST=1,IGNORE_POS=2,IGNORE_ORI=3;
let mode = SWAP;

function Cube() {
  this.selectedFacelet = null;

  this.getPiece = (facelet) => (
    Object.values(this[facelet.type]).find(value =>
      Object.values(value).find(val => val === facelet)
  ));
  

  this.swapFacelets = function (facelet1, facelet2) {
    const facelet1Elem = document.getElementById(facelet1.id);
    const facelet2Elem = document.getElementById(facelet2.id);

    const temp = facelet1Elem.style.fill;
    facelet1Elem.style.fill = facelet2Elem.style.fill
    facelet2Elem.style.fill = temp;
  }

  this.twist = function(facelet) {
    const piece = this.getPiece(facelet);

    const pieceIdx = Object.values(piece).map(facelet => facelet.id).indexOf(facelet.id);

    const pieceFacelets = reorder(Object.values(piece), pieceIdx);

    this.swapFacelets(pieceFacelets[0], pieceFacelets[1]);
    this.swapFacelets(pieceFacelets[0], pieceFacelets[2]);
  }

  this.swap = function(facelet1, facelet2) {
    const piece1 = this.getPiece(facelet1);
    const piece2 = this.getPiece(facelet2);

    if (piece1 === piece2) {
      return;
    }

    const piece1Idx = Object.values(piece1).map(facelet => facelet.id).indexOf(facelet1.id);
    const piece2Idx = Object.values(piece2).map(facelet => facelet.id).indexOf(facelet2.id);

    const piece1Facelets = reorder(Object.values(piece1), piece1Idx);
    const piece2Facelets = reorder(Object.values(piece2), piece2Idx);

    Object.values(piece1Facelets).forEach((facelet, idx) => {
      this.swapFacelets(facelet, piece2Facelets[idx]);
    });
  }
}

const cube = new Cube ();

window.getCubePieces = () => {
  console.log("EDGES");
  console.log(cube.EDGES);
  console.log("CORNERS");
  console.log(cube.CORNERS);
}

function Facelet(id, type) {
  this.id = id;
	this.type = type;

  this.deselect = function () {
    cube.selectedFacelet = null;
    document.getElementById(id).style.opacity = null;
  }

  this.select = function () {
    cube.selectedFacelet = this;
    document.getElementById(id).style.opacity = 0.7;
  }

  this.click = function() {
    switch (mode) {
			case SWAP:
				if (cube.selectedFacelet) {
					if (cube.selectedFacelet.type == this.type) {
						cube.swap(cube.selectedFacelet, this);
						
            cube.selectedFacelet.deselect();
					}
				}
				else {
          this.select();
				}
				break;
			case TWIST:
				cube.twist(this);
				break;
			default:
				break;
		}
  }
}

// TODO take puzzle param
const displayCube = () => {
  document.write(PYRA_SVG);

  const puzzle = document.getElementById('puzzle');
  Array.from(puzzle.children).forEach(element => {
    const [type, position, orientation] = element.id.split('-');
    if (type === 'CENTERS') {
      return;
    }
    const facelet = new Facelet(element.id, type, orientation);
    if (!cube[type]) {
      cube[type] = {};
    }
    cube[type][position] = {
      ...cube[type][position],
      [orientation]: facelet,
    };
    element.onclick = () => facelet.click();
  });
}