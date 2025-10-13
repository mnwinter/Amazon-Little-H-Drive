#include "ui_html.h"
// Web UI HTML stored in flash (PROGMEM)
const char index_html[] PROGMEM = R"HTML(<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Lil H Drive</title>
  <style>
    :root{font-family:system-ui,Segoe UI,Roboto,Arial,sans-serif}
    body{margin:16px;max-width:750px}
    h1{margin:0 0 8px}
    .card{border:1px solid #ccc;border-radius:12px;padding:16px;margin:12px 0;box-shadow:0 1px 4px rgba(0,0,0,.06)}
    .row{display:flex;gap:12px;flex-wrap:wrap}
    label{display:block;margin:6px 0 4px}
    input[type=range]{width:100%}
    .val{font-variant-numeric:tabular-nums}
    button{padding:10px 14px;border-radius:10px;border:1px solid #444;cursor:pointer}
    .grid{display:grid;grid-template-columns:repeat(3,80px);gap:10px;justify-content:center;align-items:center;margin-top:10px}
  </style>
</head>
<body>
  <h1>Lil H Drive</h1>
  <p>Move sliders or tap the D‑pad. Values send to <code>/api/drive?x=&y=&rot=&lift=</code>.</p>

  <div class="card">
    <div class="row">
      <div style="flex:1;min-width:240px">
        <label>Forward/Back (Y): <span id="vy" class="val">0</span></label>
        <input id="y" type="range" min="-100" max="100" value="0">
        <label>Strafe (X): <span id="vx" class="val">0</span></label>
        <input id="x" type="range" min="-100" max="100" value="0">
        <label>Rotate (Rot): <span id="vr" class="val">0</span></label>
        <input id="rot" type="range" min="-100" max="100" value="0">
        <label>Lift: <span id="vl" class="val">0</span></label>
        <input id="lift" type="range" min="-100" max="100" value="0">
        <div style="margin-top:10px" class="row">
          <button id="stop">STOP</button>
          <button id="center">Center</button>
        </div>
      </div>
      <div style="flex:0 0 260px">
        <div class="grid">
          <button data-dpad="y:100">↑</button>
          <button data-dpad="rot:0">·</button>
          <button data-dpad="y:-100">↓</button>
          <button data-dpad="x:-100">←</button>
          <button data-dpad="rot:100">⟳</button>
          <button data-dpad="x:100">→</button>
        </div>
      </div>
    </div>
  </div>

  <script>
  const qs = s => document.querySelector(s);
  const qsa = s => Array.from(document.querySelectorAll(s));
  const ui = { x:qs("#x"), y:qs("#y"), rot:qs("#rot"), lift:qs("#lift") };
  const vv = { x:qs("#vx"), y:qs("#vy"), rot:qs("#vr"), lift:qs("#vl") };

  function clamp(n){ n = Math.round(n); return Math.max(-100, Math.min(100, n)); }
  function refreshLabels(){
    vv.x.textContent = ui.x.value;
    vv.y.textContent = ui.y.value;
    vv.rot.textContent = ui.rot.value;
    vv.lift.textContent = ui.lift.value;
  }
  async function send(){
    const p = new URLSearchParams({x:ui.x.value,y:ui.y.value,rot:ui.rot.value,lift:ui.lift.value});
    try{
      await fetch(`/api/drive?${p.toString()}`, {method:"GET", cache:"no-cache"});
    }catch(e){ console.log(e); }
  }
  qsa("input[type=range]").forEach(r=>{
    r.addEventListener("input", ()=>{ refreshLabels(); send(); });
  });
  qs("#center").addEventListener("click", ()=>{
    ui.x.value=0; ui.y.value=0; ui.rot.value=0; ui.lift.value=0; refreshLabels(); send();
  });
  qs("#stop").addEventListener("click", ()=>{
    ui.x.value=0; ui.y.value=0; ui.rot.value=0; ui.lift.value=0; refreshLabels(); send();
  });
  qsa("[data-dpad]").forEach(b=>{
    b.addEventListener("mousedown", ()=>{
      const pair = b.getAttribute("data-dpad").split(":");
      const k = pair[0], v = clamp(parseInt(pair[1],10));
      ui[k].value = v; refreshLabels(); send();
    });
    b.addEventListener("mouseup", ()=>{
      // snap back to zero
      ui.x.value=0; ui.y.value=0; ui.rot.value=0; refreshLabels(); send();
    });
    b.addEventListener("mouseleave", ()=>{ /* no-op */ });
    b.addEventListener("touchstart", (e)=>{ e.preventDefault(); b.dispatchEvent(new Event("mousedown")); }, {passive:false});
    b.addEventListener("touchend", (e)=>{ e.preventDefault(); b.dispatchEvent(new Event("mouseup")); }, {passive:false});
  });
  refreshLabels();
  </script>
</body>
</html>)HTML";
