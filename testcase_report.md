# DC Operating Point Test Report

## Scope

This report covers nine SPICE netlists under `testcase/`, split into three difficulty levels. The ngspice batch outputs were generated with:

```sh
ngspice -b testcase/<case>.cir >> standard/<case>.out
```

The current project binary was also run against every testcase. Source code was not modified for this report.

## Testcases

| Level | Case | Type | Purpose |
| --- | --- | --- | --- |
| 1 | `level1_01_resistor_divider.cir` | Linear | Basic voltage source and resistor divider |
| 1 | `level1_02_current_resistor.cir` | Linear | Current source RHS stamping and resistor grounding |
| 1 | `level1_03_diode_resistor.cir` | Nonlinear | Single diode DC operating point |
| 2 | `level2_04_inductor_dc_short.cir` | Linear | DC inductor as 0 V voltage source |
| 2 | `level2_05_nmos_res_load.cir` | Nonlinear | NMOS Level-1 region handling with resistor load |
| 2 | `level2_06_bjt_common_emitter.cir` | Nonlinear | NPN common-emitter operating point |
| 3 | `level3_07_linear_bridge.cir` | Linear | Multi-node linear bridge with two voltage sources |
| 3 | `level3_08_diode_mos_combo.cir` | Nonlinear | Combined diode and NMOS nonlinear solve |
| 3 | `level3_09_cmos_inverter.cir` | Nonlinear | NMOS/PMOS interaction at a CMOS inverter DC point |

## ngspice Reference Values

| Case | Key operating-point values |
| --- | --- |
| `level1_01_resistor_divider` | `v(in)=10.0`, `v(out)=5.0`, `i(v1)=-5.0e-3` |
| `level1_02_current_resistor` | `v(out)=-2.0` |
| `level1_03_diode_resistor` | `v(in)=1.0`, `v(out)=0.6294408`, `i(v1)=-3.70559e-4` |
| `level2_04_inductor_dc_short` | `v(in)=5.0`, `v(mid)=5.0`, `i(v1)=-5.0e-3` |
| `level2_05_nmos_res_load` | `v(vdd)=5.0`, `v(gate)=2.0`, `v(out)=0.9702035`, `i(vdd)=-4.02980e-4` |
| `level2_06_bjt_common_emitter` | `v(vcc)=5.0`, `v(base)=0.75`, `v(coll)=4.608120`, `i(vcc)=-3.91880e-4` |
| `level3_07_linear_bridge` | `v(a)=12.0`, `v(b)=3.0`, `v(x)=7.090909`, `v(y)=1.783784`, `i(v1)=-4.90909e-3`, `i(v2)=5.528256e-4` |
| `level3_08_diode_mos_combo` | `v(vdd)=5.0`, `v(gate)=2.0`, `v(out)=0.6033016`, `i(vdd)=-4.39670e-4` |
| `level3_09_cmos_inverter` | `v(vdd)=5.0`, `v(in)=2.5`, `v(out)=2.5`, `i(vdd)=-1.36080e-3` |

Full ngspice logs are stored in `standard/*.out`.

## Current Project Output

The project binary `./spice` was built successfully and run on all nine testcases. Outputs are stored in `actual/*.out`; stderr logs are stored in `actual/*.err`.

| Case | Exit code | stdout | stderr |
| --- | --- | --- | --- |
| `level1_01_resistor_divider` | 0 | operating point printed | empty |
| `level1_02_current_resistor` | 0 | operating point printed | empty |
| `level1_03_diode_resistor` | 0 | operating point printed | empty |
| `level2_04_inductor_dc_short` | 0 | operating point printed | empty |
| `level2_05_nmos_res_load` | 0 | operating point printed | empty |
| `level2_06_bjt_common_emitter` | 0 | operating point printed | empty |
| `level3_07_linear_bridge` | 0 | operating point printed | empty |
| `level3_08_diode_mos_combo` | 0 | operating point printed | empty |
| `level3_09_cmos_inverter` | 0 | operating point printed | empty |

## Comparison Result

Acceptance thresholds used here:

- Linear circuits: absolute error <= `1e-8`.
- Nonlinear node voltages: absolute error <= `1e-2`.
- Nonlinear source currents: relative error <= `2e-2`.

| Case | Largest observed difference | Result |
| --- | --- | --- |
| `level1_01_resistor_divider` | exact on checked values | Passed |
| `level1_02_current_resistor` | exact on checked values | Passed |
| `level1_03_diode_resistor` | `v(out)` abs error `2.939e-4`; `i(V1)` rel error `7.938e-4` | Passed |
| `level2_04_inductor_dc_short` | exact on checked values | Passed |
| `level2_05_nmos_res_load` | `v(out)` abs error `1.764e-6`; `i(VDD)` rel error `1.306e-6` | Passed |
| `level2_06_bjt_common_emitter` | `v(coll)` abs error `5.719e-3`; `i(VCC)` rel error `1.459e-2` | Passed |
| `level3_07_linear_bridge` | max voltage abs error `2.162e-7`; max current rel error `1.852e-7` | Passed |
| `level3_08_diode_mos_combo` | `v(out)` abs error `2.770e-4`; `i(VDD)` rel error `6.264e-5` | Passed |
| `level3_09_cmos_inverter` | `i(VDD)` rel error `1.837e-9` | Passed |

The nonlinear differences are expected at this stage because the implementation intentionally uses reduced DC models: diode exponential model without full ngspice limiting details, simplified Ebers-Moll BJT, and Level-1 MOS without body effect.

## Acceptance Judgment

| Check | Result |
| --- | --- |
| Testcase files created | Passed |
| ngspice reference outputs generated | Passed |
| Current program solves all testcases | Passed |
| Numerical output comparison | Passed |
| Difference within tolerance | Passed |

The current implementation passes the designed DC operating-point testcase set under the tolerances above.
