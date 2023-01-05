#include <iostream>

#include <fftw3.h>
#include <math.h>

int main(int argc, char const *argv[]) {
  fftw_complex *in, *out;
  fftw_plan p;

  int nfft = 32;

  in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * nfft);
  out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * nfft);
  p = fftw_plan_dft_1d(nfft, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

  // Create a signal for input.
  for (int i = 0; i < nfft; i++) {
    in[i][0] = (sin(i * 2 * M_PI * (1 / (double)nfft)) +
                sin(i * 2 * M_PI * (2 / (double)nfft)) +
                sin(i * 2 * M_PI * (5 / (double)nfft)));
    in[i][1] = 0;
    std::cout << "Time " << (double)i / (double)nfft << ", value: " << in[i][0]
              << std::endl;
  }

  fftw_execute(p); /* repeat as needed */

  // Print the output result.
  for (int i = 0; i < nfft / 2; i++) {
    // std::cout << "Freq " << i << ": " << out[i][0] << " + " << out[i][1] <<
    // "i" << std::endl;
    double magnitude = sqrt(pow(out[i][0], 2) + pow(out[i][1], 2));
    std::cout << "Freq " << i << ": " << magnitude << std::endl;
  }

  fftw_destroy_plan(p);
  fftw_free(in);
  fftw_free(out);
  return 0;
}