<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <title>Electron Rise & Fall — Interactive</title>
  <style>
    :root{--bg:#0f1724;--card:#0b1220;--accent:#60a5fa;--muted:#94a3b8}
    body{font-family:Inter,system-ui,Segoe UI,Roboto,Arial; margin:0; background:linear-gradient(180deg,#071023 0%, #071827 100%); color:#e6eef8; display:flex; min-height:100vh; align-items:center; justify-content:center}
    .app{width:950px; max-width:96vw; background:var(--card); border-radius:12px; padding:18px; box-shadow:0 8px 30px rgba(2,6,23,.6)}
    header{display:flex; gap:12px; align-items:center}
    h1{margin:0; font-size:18px}
    .controls{display:grid; grid-template-columns:repeat(4,1fr); gap:12px; margin-top:14px}
    .control{background:rgba(255,255,255,0.02); padding:10px; border-radius:8px}
    label{display:block; font-size:12px; color:var(--muted)}
    input[type=range]{width:100%}
    input[type=number]{width:100%; padding:6px; border-radius:6px; border:1px solid rgba(255,255,255,0.04); background:transparent; color:inherit}
    .canvas-wrap{display:flex; gap:12px; margin-top:16px}
    canvas{background:linear-gradient(180deg,#021426 0%, #00101a 100%); border-radius:8px; width:640px; height:400px}
    .right{flex:1; min-width:220px}
    .buttons{display:flex; gap:8px; margin-top:8px}
    button{background:var(--accent); color:#022; padding:8px 10px; border-radius:8px; border:none; cursor:pointer}
    .small{background:transparent; border:1px solid rgba(255,255,255,0.06); color:var(--muted)}
    .info{font-size:13px; color:var(--muted); margin-top:10px}
    .footer{font-size:12px; color:var(--muted); margin-top:12px}
    .stat{display:flex; justify-content:space-between; margin-top:6px}
    .toggle{display:flex; gap:6px; align-items:center}
    .legend{display:flex; gap:8px; align-items:center; margin-top:8px}
    .dot{width:12px; height:12px; border-radius:50%; background:var(--accent)}
  </style>
</head>
<body>
  <div class="app">
    <header>
      <h1>Electron Rise & Fall — Interactive diagram</h1>
      <div style="margin-left:auto; color:var(--muted); font-size:13px">Model: simple sinusoidal motion y(t) = (e/m) × Yscale × sin(2π v t)</div>
    </header>

    <div class="controls">
      <div class="control">
        <label>Charge (e)</label>
        <input id="eRange" type="range" min="-200" max="200" value="-160" step="1">
        <input id="eNum" type="number" value="-160" step="1">
        <div class="info">Normalized units (toggle SI to use raw e = -1.602e-19 C)</div>
      </div>

      <div class="control">
        <label>Frequency / Velocity (v) — Hz</label>
        <input id="vRange" type="range" min="0.1" max="10" value="1" step="0.1">
        <input id="vNum" type="number" value="1" step="0.1">
        <div class="info">Higher value → faster oscillation</div>
      </div>

      <div class="control">
        <label>Mass (m)</label>
        <input id="mRange" type="range" min="0.1" max="400" value="9.11" step="0.01">
        <input id="mNum" type="number" value="9.11" step="0.01">
        <div class="info">Normalized units (toggle SI to use electron mass ≈ 9.109e-31 kg)</div>
      </div>

      <div class="control">
        <label>Y scale (visual amplitude)</label>
        <input id="yRange" type="range" min="0.1" max="300" value="80" step="0.1">
        <input id="yNum" type="number" value="80" step="0.1">
        <div class="info">How much the electron moves on screen (pixels multiplier)</div>
      </div>
    </div>

    <div class="canvas-wrap">
      <canvas id="cnv" width="640" height="400"></canvas>
      <div class="right">
        <div class="buttons">
          <button id="play">Play</button>
          <button id="pause" class="small">Pause</button>
          <button id="reset" class="small">Reset</button>
          <button id="siToggle" class="small">Use SI constants</button>
        </div>

        <div class="legend">
          <div class="dot"></div>
          <div style="font-size:13px">Electron</div>
        </div>

        <div class="stat"><div>t (s)</div><div id="tVal">0.00</div></div>
        <div class="stat"><div>y (px)</div><div id="yVal">0.0</div></div>
        <div class="stat"><div>Instant. velocity</div><div id="velVal">0.0</div></div>

        <div class="info"> 
