/* Copyright (C) 2015 Hans-Kristian Arntzen <maister@archlinux.us>
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GLFFT_CLI_HPP__
#define GLFFT_CLI_HPP__

#include <functional>

namespace GLFFT
{
    namespace Internal
    {
        struct TestSuiteArguments
        {
            unsigned test_id_min = 0;
            unsigned test_id_max = 0;
            bool exhaustive = true;
            bool throw_on_fail = false;
            double min_snr_fp16 = 50.0;
            double min_snr_fp32 = 100.0;
            double epsilon_fp16 = 1e-3;
            double epsilon_fp32 = 1e-6;
        };

        void run_test_suite(const TestSuiteArguments &args);
    }

    int cli_main(
            const std::function<void* ()> &create_context,
            const std::function<void (void*)> &destroy_context,
            int argc, char *argv[]) noexcept;
}

#endif
