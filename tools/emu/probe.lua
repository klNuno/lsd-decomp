-- Loaded first by tools/emu/run.sh. Counts vsyncs, prints registers, captures frames, quits.
local function env(name, default) return tonumber(os.getenv(name) or "") or default end
local function hex(v) return string.format("0x%08x", tonumber(v) % 4294967296) end
local maxFrames = env("LSD_EMU_FRAMES", 1800)
local regsEvery = env("LSD_EMU_REGS", 0)
local out = os.getenv("LSD_EMU_OUT") or "captures"
local shots = {}
for n in string.gmatch(os.getenv("LSD_EMU_SHOTS") or "", "%d+") do shots[tonumber(n)] = true end

LsdEmu = { frame = 0, hex = hex }

local function capture(frame)
  local ss = PCSX.GPU.takeScreenShot()
  local bpp = tonumber(ss.bpp) == 1 and 24 or 16
  local name = string.format("%s/frame%05d-%dx%d-%d.raw", out, frame, ss.width, ss.height, bpp)
  local f = Support.File.open(name, "TRUNCATE")
  f:writeMoveSlice(ss.data)
  f:close()
  print("capture " .. name)
end

LsdEmu.listener = PCSX.Events.createEventListener("GPU::Vsync", function()
  LsdEmu.frame = LsdEmu.frame + 1
  local frame = LsdEmu.frame
  if regsEvery > 0 and frame % regsEvery == 0 then
    local r = PCSX.getRegisters()
    print(string.format("frame %d pc %s gp %s sp %s ra %s", frame, hex(r.pc), hex(r.GPR.n.gp), hex(r.GPR.n.sp), hex(r.GPR.n.ra)))
  end
  if shots[frame] then capture(frame) end
  if frame >= maxFrames then PCSX.quit(0) end
end)
