/*
 * Small RV64IM correctness and performance test.
 *
 * It intentionally has no libc dependency.  The fixed 256-iteration loop
 * gives a repeatable workload for comparing cycle counts between processor
 * revisions.  The return value is the pass/fail result:
 *   0 = pass
 *   1 = checksum failure
 *   2 = branch/invariant failure
 */

typedef long long s64;

static __attribute__((noinline)) s64
mul_div_rem(s64 value, s64 divisor)
{
  return value * divisor + value / divisor + value % divisor;
}

int main(void)
{
  volatile s64 data[64];
  s64 checksum = 0;
  s64 i;

  for (i = 0; i < 256; i++) {
    s64 index = i & 63;
    s64 value = mul_div_rem(i + 11, (i % 7) + 3);

    data[index] = value ^ (i * 13);
    checksum += data[index];
  }

  /*
   * This constant was calculated independently from the loop above.  It
   * detects incorrect arithmetic, loads, stores, branches, and loop control.
   */
  if (checksum != 431232)
    return 1;

  if (data[0] != 3368 || data[63] != 2713)
    return 2;

  return 0;
}
