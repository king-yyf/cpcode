export PATH=$PATH:/Users/yangyf/Desktop

cf_id=527272
cf race $cf_id

python3 gen_sublime_test_case_gym.py $cf_id

echo "cf submit -f cf/gym/${cf_id}/\$1.cpp ${cf_id}\$1" > submit.sh

cd `dirname $0`
cd cf/gym/${cf_id}

open *.cpp

echo "init finished!"
