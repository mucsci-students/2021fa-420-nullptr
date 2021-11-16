function toggleSidebar() {
  var x = document.getElementById("umlsidebar");
  if (x.style.display === "none") {
    x.style.display = "block";
  } else {
    x.style.display = "none";
  }
  getDiagramImage();
}
