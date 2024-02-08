//# Convert 32->16
//# permute stuff

// g++ -mavx2
#include <immintrin.h>
#include <cstdio>
#include <cstring>

int main(int argc, char* argv[])
{
  //  __m256i first = _mm256_set_epi32(7,6,5,4,3,2,1,0);
  //__m256i second = _mm256_set_epi32(15,14,13,12,11,10,9,8);

  //  _mm256_permutexvar_epi16(
#if 0
  __m128i v_in = _mm_setr_epi16(0, 1, 2, 3, 4, 5, 6, 7);
  __m128i v_perm = _mm_setr_epi8(0, 1,
				 8, 9,
				 2, 3,
				 10, 11,
				 4, 5,
				 12, 13,
				 6, 7,
				 14, 15);
  __m128i v_out = _mm_shuffle_epi8(v_in, v_perm); // pshufb

  alignas(16) short in[8];
  alignas(16) short out[8];
  memcpy(out, &v_out, 8*sizeof(short));
  memcpy(in, &v_in, 8*sizeof(short));

  for (int i = 0 ; i < 8 ; i++)
    printf("%d ", in[i]);

  printf("\n");
  for (int i = 0 ; i < 8 ; i++)
    printf("%d ", out[i]);
#endif
  __m256i v_in = _mm256_setr_epi32(0,1,2,3,4,5,6,7);

  // Move
  __m128i v_lower = _mm_castps_si128(_mm256_extractf128_ps(_mm256_castsi256_ps(v_in), 0));
  __m128i v_upper = _mm_castps_si128(_mm256_extractf128_ps(_mm256_castsi256_ps(v_in), 1));
  // 2xgather, 2xscatter
  // Use permute mask
  // And lower and higher part

  // _mm_move_epi64 -> copy to lower and zero upper.
  
  //   __m128 lo = _mm_movelh_ps(vec, _mm_setzero_ps());
  //  __m128 hi = _mm_movehl_ps(vec, _mm_setzero_ps());

  
  /*
  __m128i v_perm = _mm_setr_epi8(0, 1,
				 8, 9,
				 2, 3,
				 10, 11,
				 4, 5,
				 12, 13,
				 6, 7,
				 14, 15);
  */
  
  alignas(32) int in[8];
  alignas(16) int lower[4];
  alignas(16) int upper[4];
  memcpy(in, &v_in, 8*sizeof(int));
  for (int i = 0 ; i < 8 ; i++)
    printf("%d ", in[i]);
  printf("\n");
  memcpy(lower, &v_lower, 8*sizeof(int));
  memcpy(upper, &v_upper, 8*sizeof(int));

  for (int i = 0 ; i < 4 ; i++)
    printf("%d ", lower[i]);
  printf("\n");
  for (int i = 0 ; i < 4 ; i++)
    printf("%d ", upper[i]);
  printf("\n");
  
  
  return 0;
}


#if 0


If it is safe to read from/write to the two bytes after the last index, this should work as well:

void scatter2(uint16_t *array, __m256i vindex, __m256i a) {
  __mmask8 odd = _mm256_test_epi32_mask(vindex, _mm256_set1_epi32(1));

  int32_t* arr32 = (int32_t*)array;
  __m256i was_odd = _mm256_i32gather_epi32(arr32, vindex, 2);

  __m256i data_even = _mm256_mask_blend_epi16(0x5555, was_odd, a);
  _mm256_mask_i32scatter_epi32(array, ~odd, vindex, data_even, 2);
  __m256i was_even = _mm256_i32gather_epi32(arr32, vindex, 2);

  __m256i data_odd = _mm256_mask_blend_epi16(0x5555, was_even, a);
  _mm256_mask_i32scatter_epi32(array, odd, vindex, data_odd, 2);
}
If you could guarantee that indexes in vindex are increasing (or at least for any partially conflicting {i, i+1} in vindex i+1 comes after i), you can probably get away with a single gather+blend+scatter. Also, it might be beneficial to use masked gathers (i.e., each time only gather the elements which you overwrite next) -- I'm not sure if this has an impact on throughput. Finally, the _mm256_mask_blend_epi16 could actually be replaced by a simple _mm256_blend_epi16.
#endif

