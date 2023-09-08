#include <stdio.h>
#include <assert.h>

struct CountsBySoH {
  int healthy;
  int exchange;
  int failed;
};

struct CountsBySoH countBatteriesByHealth(const int* presentCapacities, int nBatteries) {
  struct CountsBySoH counts = {0, 0, 0};
  int i=0;
  float soh;
  for(i=0;i<nBatteries;i++){
    soh = (float)(100*presentCapacities[i]/120);
    if(soh<65) counts.failed++;
    else if(soh>=65 && soh<=80) counts.exchange++;
    else counts.healthy++;
  }
  return counts;
}

void testBucketingByHealth() {
  // test case 1
  const int presentCapacities[] = {115, 118, 80, 95, 91, 77};
  const int numberOfBatteries = sizeof(presentCapacities) / sizeof(presentCapacities[0]);
  printf("Counting batteries by SoH...test 1\n");
  struct CountsBySoH counts = countBatteriesByHealth(presentCapacities, numberOfBatteries);
  assert(counts.healthy == 2);
  assert(counts.exchange == 3);
  assert(counts.failed == 1);
  printf("Done counting test 1:)\n");  // this part of code will run correctly 
  
  // 2nd test case
  const int presentCapacities2[] = {115,118,119,80,95,91,77}; // now here error because of 119 thus healthy=3
  const int numberOfBatteries2 = sizeof(presentCapacities2) / sizeof(presentCapacities2[0]);
   printf("Counting batteries by SoH...test 2\n");
  struct CountsBySoH counts2 = countBatteriesByHealth(presentCapacities2, numberOfBatteries2);
  assert(counts2.healthy == 2);  // now here error will be shown as healthy=3
  assert(counts2.exchange == 3);
  assert(counts2.failed == 1);
  printf("Done counting test 2:)\n"); 
  
   // 3rd test case
  const int presentCapacities3[] = {115,118,96,80,95,91,77}; // now here error because of 96 exchange=4
  const int numberOfBatteries3 = sizeof(presentCapacities3) / sizeof(presentCapacities3[0]);
   printf("Counting batteries by SoH...test 3\n");
  struct CountsBySoH counts3 = countBatteriesByHealth(presentCapacities3, numberOfBatteries3);
  assert(counts3.healthy == 2); 
  assert(counts3.exchange == 3);  // now here error will be shown as exchange=4
  assert(counts3.failed == 1);
  printf("Done counting test 3:)\n"); 
  
    // 4th test case
  const int presentCapacities4[] = {115,118,60,80,95,91,77}; // now here error because of 60 failed=2
  const int numberOfBatteries4 = sizeof(presentCapacities4) / sizeof(presentCapacities4[0]);
   printf("Counting batteries by SoH...test 4\n");
  struct CountsBySoH counts4 = countBatteriesByHealth(presentCapacities4, numberOfBatteries4);
  assert(counts4.healthy == 2); 
  assert(counts4.exchange == 3);
  assert(counts4.failed == 1);   // now here error will be shown as failed = 2
  printf("Done counting test 4:)\n"); 
}

int main() {
  testBucketingByHealth();
  return 0;
}
