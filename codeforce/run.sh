export PATH=$PATH:/Users/yangyf/Desktop

cf_id=1997
cf race $cf_id

python3 gen_sublime_test_case.py $cf_id


echo "cf submit -f cf/contest/${cf_id}/\$1.cpp ${cf_id}\$1" > submit.sh

cd `dirname $0`
cd cf/contest/${cf_id}

open *.cpp

echo "init finished!"
