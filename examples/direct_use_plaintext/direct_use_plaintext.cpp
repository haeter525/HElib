/* Copyright (C) 2019-2021 IBM Corp.
 * This program is Licensed under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. See accompanying LICENSE file.
 */

// This is a sample program for education purposes only.
// It attempts to show the various basic mathematical
// operations that can be performed on both ciphertexts
// and plaintexts.

#include <iostream>
#include <string>
#include <cmath>

#include <helib/helib.h>

void getSensitiveData(std::vector<char>& vec)
{
  vec.push_back('d');
  vec.push_back('a');
  vec.push_back('t');
  vec.push_back('a');
}

void expose(helib::Ptxt<helib::BGV> data) { std::cout << data; }
void expose(helib::Ctxt data) { std::cout << data; }

int main(int argc, char* argv[])
{

  helib::Context context = helib::ContextBuilder<helib::BGV>()
                               .m(32109)
                               .p(4999)
                               .r(1)
                               .bits(128)
                               .c(2)
                               .build();

  helib::SecKey secret_key(context);
  secret_key.GenSecKey();

  helib::addSome1DMatrices(secret_key);
  const helib::PubKey& public_key = secret_key;
  const helib::EncryptedArray& ea = context.getEA();

  std::vector<char> plaintext;
  getSensitiveData(plaintext);

  helib::Ptxt<helib::BGV> ptxt(context, plaintext);

  helib::Ctxt ctxt(secret_key);
  public_key.Encrypt(ctxt, ptxt);

  expose(ctxt);
  expose(ptxt);

  return 0;
}
