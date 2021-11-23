var boxes = new Map();
var lines = new Array();
var classesJson;
var json_string;
var relationshipsJson;
SVG.on(document, 'DOMContentLoaded', function() {
  var draw = SVG().addTo('svg');

  //add panning and zooming
  svgPanZoom('#umldiagram', {
    dblClickZoomEnabled: false
  });

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
    let line = draw.line(source.x()+100, source.y()+150, dest.x()+100, dest.y()+150).stroke({ color: 'black', width: 10, linecap: 'round' });
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
 // nested.rect(200,200).attr({ fill: '#f00', opacity: 0.3, width: 150, height: 150  }).front();
  var xval_rect = 150;
  var yval_rect = 150;
  var nested = draw.nested()
  var rect = nested.rect(xval_rect,yval_rect).radius(10).css({fill: '#555', resize: 'both', overflow: 'auto', stroke: 'black'});

  var text_y = 20;
  var text_x = 10;
  nested.text(uclass["name"]).dy(text_y).dx(text_x);
  text_y += 20;

// const textElement = document.querySelector('text')  
//const bbox = textElement.getBBox();  
//const {width} = bbox;  
//var w =console.log(width);
//if(width >=150){
    
//  xval_rect += 10;
//}

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
    //force textbox back on screen for Y values
    if(nested.y() < 0){
      nested.y(1);
    }
    else if(nested.y() > 1500){
      nested.y(1300);
    }
    //force textbox back on screen for x values
    else if(nested.x() < 0){
      nested.x(1)
    }
    else if(nested.x() > 3000){
      nested.x(2700);
    }
    //send position to server
    request = new XMLHttpRequest();
    request.open("GET", '/position/' + uclass["name"] + '/' + Math.floor(nested.x()) + '/' + Math.floor(nested.y(), true));
    request.send();

    //get new json string for saving
    var json_string_request = new XMLHttpRequest;
    json_string_request.open('GET', '/save/data');
    
    // If specified, responseType must be empty string or "document"
    json_string_request.responseType = 'text';
    
    json_string_request.onload = function () {
      if (json_string_request.readyState === json_string_request.DONE && json_string_request.status === 200) {
        json_string = json_string_request.responseText;
      }
    };
    
    json_string_request.send();

    //draw the relationship lines after each drag
    drawLines(draw);
  });

  //redraw lines after move
  nested.draggable().on('dragmove', e => {
    drawLines(draw);
  });
    
}

function sendDiagramInfo(classes_in, relationships_in, json_string_in)
{
  classesJson = classes_in;
  relationshipsJson = relationships_in;
  json_string = JSON.stringify(json_string_in);
}

function getDiagramImage()
{
  var canvas = document.getElementById("umlcanvas");
  canvas.height = 1500;
  canvas.width = 3000;
  const ctx = canvas.getContext("2d");
  drawInlineSVG(document.getElementById('umldiagram'), ctx, function() {
    img = canvas.toDataURL();
    download(img, "diagram");
  });
}

//for saving file
function save()
{
  window.location = "/save";
  document.addEventListener('DOMContentLoaded', function () {
    alert("page loaded");
  });
  window.onload = download('data:text/plain;charset=utf-8,' + encodeURIComponent(json_string), "diagram.json");
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