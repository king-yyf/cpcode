import math

import pandas as pd
from os import listdir
from os.path import isfile, join
import numpy as np

path = "/home/web_server/yangyunfei/pipeline/hive/p_date=20231018"

select_columns = [
    "action_client_block_count", "action_client_block_dur"
]
D = pd.DataFrame()
for da in ["1009", "1010", "1011","1012", "1018","1027","1028","1029","1030","1031"]:
    path = "/home/web_server/yangyunfei/pipeline/hive/p_date=2023" + da
    for file_name in listdir(path):
        if isfile(join(path, file_name)):
            if file_name.startswith("part"):
                df = pd.read_parquet(join(path, file_name),engine='pyarrow', columns = select_columns)
                df = df[df['action_client_block_count'] > 0]
                df.drop(['action_client_block_count'], axis=1, inplace=True)
                D = D.append(df)
                    
    print(da, 'finish')

ND = D.to_numpy()
np.save('block_dur.npy', ND)

