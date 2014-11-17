/*
 * Csv.cpp
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#include <stdio.h>
#include "Csv.h"
#include "datastruct/Records.h"
#include "mem/Buffer.h"
#include "hack/Assert.h"

namespace Smartdb {

Csv::Csv()
: read_buf(10 * 1e6)
{
}

Csv::~Csv() {
	// TODO Auto-generated destructor stub
}

/**
 * うーん、freadで使うバッファとRecordたちを載せるバッファを一緒にするのは愚策かも。
 * freadバッファ1に対しRecordの領域が10とかだったら、塗りつぶしコピーになっちゃうし。
 * Csv engine のconfigでinital_read_buffer_sizeというのを設けて、
 * |***********************|  (read)
 * |-------------------****|  (digest)
 * |****-------------------|  (memcpy)
 * |***********************|  (read)
 * という風に使っていく。
 * ただし、digestが全く出来ないほどRecordが大きいのであれば、仕方がないのでbuffer_sizeを
 * 倍々にしていく。

 * あと、Csvのコンストラクタで予め「読むべきカラムの順序付きリスト」を渡されていて、かつ
 * 先頭行を読んで何番目にどのカラムがあるか分かっているようにする。
 * すなわち、SELECT age, sex from CSV; でかつCSVファイルが "id,sex,age" で始まっていたら、
 * { 2番目のCSVカラム => Recordの1番目のカラム,
 *   3 => 2 }
 * というデータ構造を持っているべき。
 *
*/
SmartdbErr Csv::read_records(Records &records, size_t n_records) {
  //freadでread_buf埋める

  /*
  lines in read_buf.readline()
      cols in lines.split(',')
        size_t col_idx;
        for (size_t i = 0; i < records.coldefs.size(); ++i)
          col_idx = cols.search(records.coldefs[i].name);
        records.columns[col_idx]->add(cols[col_idx]);
        */
  return NO_ERR;
}

} /* namespace Smartdb */
