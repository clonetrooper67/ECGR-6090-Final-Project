import m5
from m5.objects import *
from m5.util import *
import ConfigParser
from HWAccConfig import *


def makeHWAcc(options, system):
    hw_path = options.accpath + "/" + options.accbench + "/hw/"

    ############################# Creating the Accelerator Cluster #################################
    # Create a new Accelerator Cluster
    system.convAcc    = AccCluster()
    local_low       = 0x2F000000
    local_high      = 0x2FFFFFFF
    local_range     = AddrRange(local_low, local_high)
    external_range  = [AddrRange(0x00000000, local_low-1),
                       AddrRange(local_high+1, 0xFFFFFFFF)]
    system.convAcc._attach_bridges(system, local_range, external_range)
    system.convAcc._connect_caches(system, options, l2coherent=False)
    gic = system.realview.gic

    ############################# Adding Devices to Cluster ##################################
    # Add the top function
    # The top function manages the DMA and bench accelerator, and is used to measure the
    # total system execution time, including data movement.
    acc = "top"
    config = hw_path + acc + ".ini"
    ir = hw_path + acc + ".ll"
    system.convAcc.top = CommInterface(devicename=acc, gic=gic)
    AccConfig(system.convAcc.top, config, ir)
    system.convAcc._connect_hwacc(system.convAcc.top)

    # system.convAcc.bench.enable_debug_msgs = True

    # if acc == "fft":
    #     max_req_size = 8
    #     buffer_size = 48
    # elif acc == "gemm":
    #     max_req_size = 8
    #     buffer_size = 64
    # elif acc == "md-knn":
    #     max_req_size = 4
    #     buffer_size = 24
    # elif acc == "stencil2d":
    #     max_req_size = 4
    #     buffer_size = 24
    # elif acc == "stencil3d":
    #     max_req_size = 4
    #     buffer_size = 32
    # else:
    max_req_size = 4
    buffer_size = 32

    # Add the cluster DMA
    system.convAcc.dma = NoncoherentDma(pio_addr=0x2FF00000, pio_size=21, gic=gic, int_num=98)
    system.convAcc.dma.cluster_dma = system.convAcc.local_bus.slave
    system.convAcc.dma.dma = system.convAcc.coherency_bus.slave
    system.convAcc.dma.pio = system.convAcc.top.local
    system.convAcc.dma.max_req_size = max_req_size
    system.convAcc.dma.buffer_size = buffer_size

    # addr = local_low + 0x0041
    # system.convAcc.stream_dma = StreamDma(pio_addr=addr, pio_size=32, gic=gic, max_pending=32)
    # system.convAcc.stream_dma.stream_addr=addr+32
    # system.convAcc.stream_dma.stream_size=8
    # system.convAcc.stream_dma.pio_delay='1ns'
    # system.convAcc.stream_dma.rd_int = 210
    # system.convAcc.stream_dma.wr_int = 211
    # system.convAcc._connect_dma(system, system.convAcc.stream_dma)
    # system.convAcc.stream_dma.dma = system.convAcc.coherency_bus.slave
    # system.convAcc.stream_dma.pio = system.convAcc.top.local

    # system._connect_dma(system, system.convAcc.stream_dma)

    # Add the benchmark function
    acc = options.accbench
    config = hw_path + acc + ".ini"
    ir = hw_path + acc + ".ll"
    system.convAcc.bench = CommInterface(devicename=acc, gic=gic, reset_spm=False)
    AccConfig(system.convAcc.bench, config, ir)
    system.convAcc.bench.pio = system.convAcc.top.local

    # Add the Scratchpad Memory for Kernel
    # spmRange = AddrRange(addr, addr+(80*2*24))
    system.convAcc.spm = ScratchpadMemory()#range=spmRange)
    AccSPMConfig(system.convAcc.bench, system.convAcc.spm, config)
    system.convAcc._connect_spm(system.convAcc.spm)

    # Add the Output Buffer
    # addr = local_low + 0x18E5
    # clstr.DWConvOut = StreamBuffer(stream_address=addr, stream_size=1, buffer_size=8)
    # clstr.DWConv.stream = clstr.DWConvOut.stream_in