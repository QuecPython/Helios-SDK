#!/bin/sh
py_dir=$1
out_dir=$2
app_bin=$3
QUECTEL_PROJECT=$4
app_version=$5

echo py_dir=${py_dir}
echo out_dir=${out_dir}
echo app_bin=${app_bin}
echo QUECTEL_PROJECT=${QUECTEL_PROJECT}
echo app_version=${app_version}

python -V

echo PY=${PY2}

${PY2} ${py_dir}/ota_bin_generator.py ${out_dir} ${app_bin}.bin application ${app_version} ${QUECTEL_PROJECT}
${PY2} ${py_dir}/merge_bin_generator.py ${out_dir}  ${app_bin}.bin ${app_bin}_merge.bin ${app_version} ${QUECTEL_PROJECT}