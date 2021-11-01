
var boxes = new Map();
var classesJson;
var relationshipsJson;

SVG.on(document, 'DOMContentLoaded', function() {
  var draw = SVG().addTo('svg');
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
  //relationships
  for (let relKey in relationshipsJson)
  {
    let relationship = relationshipsJson[relKey];
    let source = boxes.get(relationship["source"]);
    let dest = boxes.get(relationship["destination"]);
    draw.line(source.x()+100, source.y()+100, dest.x()+100, dest.y()+100).stroke({ color: 'blue', width: 10, linecap: 'round' }).back()
  }
})

function createClassBox(draw, uclass, x, y)
{
  var nested = draw.nested();
  nested.rect(200,200).attr({ fill: 'pink' });
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
  //drag event
  nested.draggable().on('dragend', e =>
  {
    location.href = '/position/' + uclass["name"] + '/' + nested.x() + '/' + nested.y();
  });

  boxes.set(uclass["name"], nested);
}

function setJsonText(classes_in, relationships_in)
{
  classesJson = classes_in;
  relationshipsJson = relationships_in;
}
