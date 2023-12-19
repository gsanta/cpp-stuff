#include <iostream>
#include <uuid.h>
#include <calc.h>

int get_double_amount(int amount);

int main()
{
  auto str = "47183823-2574-4bfd-b411-99ed177d3e43";
  auto id = uuids::uuid::from_string(str);

  std::cout << "amount: " << get_double_amount(2) << std::endl;
  std::cout << "uuid: " << uuids::to_string(id.value()) << std::endl;
  std::cout << "magic number: " << calc_magic_number() << std::endl;
  std::cout << "magic number: " << calc_magic_number_from_shared_lib() << std::endl;
}
