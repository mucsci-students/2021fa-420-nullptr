var boxes = new Map();
var lines = new Array();
var classesJson;
var relationshipsJson;


var panzoom;

//keeps track of current panning and zooming
var pan_x;
var pan_y;
var zoom;

SVG.on(document, 'DOMContentLoaded', function() {
  var draw = SVG().addTo('svg');

  //add panning and zooming
  panzoom = svgPanZoom('#umldiagram', {
    onZoom: function(newZoom) {
      zoom = newZoom;
    },
    onPan: function(newPan) {
      pan_x = newPan.x;
      pan_y = newPan.y;
    }
  });

  panzoom.zoomAtPoint(zoom, {x: pan_x, y: pan_y});

  draw.rect(0, 0).attr({ fill: '#FFF', width: 3000, height: 1500}).back();

  //classes
  for (let key in classesJson)
  {
    let uclass = classesJson[key];
    //if position is (0,0) (likely new class) move out so user can see while toggle is out
    var pos_x, pos_y;
    if (uclass["position_x"] == 0 && uclass["position_y"] == 0)
    {
      pos_x = 1000;
      pos_y = 350;
    } else {
      pos_x = uclass["position_x"];
      pos_y = uclass["position_y"];
    }
    createClassBox(draw, uclass, pos_x, pos_y);
  }

  drawLines(draw);
})

//draw relationship lines
function drawLines(draw)
{
  for (let relKey in relationshipsJson)
  {
    clearLines();
    let relationship = relationshipsJson[relKey];
    let source = boxes.get(relationship["source"]);
    let dest = boxes.get(relationship["destination"]);
    let line = draw.line(source.x()+100, source.y()+100, dest.x()+100, dest.y()+100).stroke({ color: 'blue', width: 10, linecap: 'round' });
    lines.push(line);
  }
}

function clearLines()
{
  lines.forEach(function (line) {
    line.remove();
  })
}

function createClassBox(draw, uclass, x, y)
{
  var nested = draw.nested();
  nested.rect(200,200).attr({ fill: '#f00', opacity: 0.3, width: 150, height: 150  }).front();
  var text_y = 20;
  var text_x = 15;
  nested.text(uclass["name"]).dy(text_y).dx(text_x);
  text_y += 20;

  //fields
  for (let key in uclass["fields"])
  {
    let field = uclass["fields"][key];
    nested.text(field["type"] + " " + field["name"]).dy(text_y).dx(text_x);
    text_y += 20;
  }

  //methods
  for (let key in uclass["methods"])
  {
    let method = uclass["methods"][key];
    var param_list = "";
    for (let param_key in method["params"])
    {
      let param = method["params"][param_key];
       param_list += param["type"] + ", ";
    }
    //get rid of last comma
    param_list = param_list.substring(0, param_list.length - 2);
    nested.text(method["return_type"] + " " + method["name"] + "(" + param_list + ")").dy(text_y).dx(text_x);
    text_y += 20;
  }
  nested.x(x).y(y);
  boxes.set(uclass["name"], nested);

  //drag event
  nested.draggable().on('dragend', e =>
  {
    request = new XMLHttpRequest();
    request.open("GET", '/position/' + uclass["name"] + '/' + Math.floor(nested.x()) + '/' + Math.floor(nested.y(), true));
    request.send();
  });

  //redraw lines after move
  nested.draggable().on('dragmove', e => {
    drawLines(draw);
  });

}

function sendDiagramInfo(classes_in, relationships_in, screenPos)
{
  classesJson = classes_in;
  relationshipsJson = relationships_in;
  pan_x = screenPos["x"];
  pan_y = screenPos["y"];
  zoom = screenPos["zoom"];
}

function getDiagramImage()
{
  var canvas = document.getElementById("umlcanvas");
  canvas.height = 1500;
  canvas.width = 3000;
  const ctx = canvas.getContext("2d");
  drawInlineSVG(document.getElementById('umldiagram'), ctx, function() {
    img = canvas.toDataURL();
    download(img);
  });
}

function download(file, name)
{
  var link = document.createElement("a");
  link.download = name;
  link.href = file;
  document.body.appendChild(link);
  link.click();
  document.body.removeChild(link);
  delete link;
}

function drawInlineSVG(svgElement, ctx, callback) {
  var svgURL = new XMLSerializer().serializeToString(svgElement);
  var img = new Image();
  img.onload = function() {
    ctx.drawImage(this, 0, 0);
    callback();
  }

  img.src = 'data:image/svg+xml; charset=utf8, ' + encodeURIComponent(svgURL);

}