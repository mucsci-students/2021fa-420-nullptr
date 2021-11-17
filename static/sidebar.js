function toggleSidebar() {
  var istoggled = false;
  var x = document.getElementById("umlsidebar");
  if (x.style.display === "none") {
    x.style.display = "block";
     istoggled = true;
  } else {
    x.style.display = "none";
     istoggled = false;
  }
}
