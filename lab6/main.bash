#!/bin/bash

generate() {
  local count="$1"
  local source_file="$2"
  local start_char="$3"
  local dir="$4"

  if [[ ! -f "$source_file" ]]; then
    echo "Исходный файл не найден: $source_file"
    exit 1
  fi

  if ! [[ "$count" =~ ^[0-9]+$ ]]; then
    echo "Количество копий должно быть неотрицательным целым числом: $count"
    exit 1
  fi

  mkdir -p "$dir"

  digits=({0..9})
  lowercase=({a..z})
  uppercase=({A..Z})

  local char_set=""
  local start=-1
  for i in "${!digits[@]}"; do
    if [[ "${digits[i]}" == "$start_char" ]]; then
      char_set="digits"
      start=$i
      break
    fi
  done

  if [[ $start -eq -1 ]]; then
    for i in "${!lowercase[@]}"; do
      if [[ "${lowercase[i]}" == "$start_char" ]]; then
        char_set="lowercase"
        start=$i
        break
      fi
    done
  fi

  if [[ $start -eq -1 ]]; then
    for i in "${!uppercase[@]}"; do
      if [[ "${uppercase[i]}" == "$start_char" ]]; then
        char_set="uppercase"
        start=$i
        break
      fi
    done
  fi

  if [[ $start -eq -1 ]]; then
    echo "Неправильный начальный символ: $start_char"
    exit 1
  fi

  file_name=$(basename "$source_file")
  base_name="$file_name"
  extension=""

  if [[ "$file_name" == *.* && ( "$file_name" != .* || "$file_name" == *.*.* ) ]]; then
    base_name="${file_name%.*}"
    extension=".${file_name##*.}"
  fi

  for ((i = 0; i < count; i++)); do
    local cur=$(( start + i))
    local cur_char

    if [[ "$char_set" == "digits" ]]; then
      if [[ $cur -ge ${#digits[@]} ]]; then
        echo "Превышен диапазон символов для $char_set"
        exit 1
      fi
      cur_char="${digits[$(( (start + i) % ${#digits[@]} ))]}"
    elif [[ "$char_set" == "lowercase" ]]; then
      if [[ $cur -ge ${#lowercase[@]} ]]; then
        echo "Превышен диапазон символов для $char_set"
        exit 1
      fi
      cur_char="${lowercase[$(( (start + i) % ${#lowercase[@]} ))]}"
    else
      if [[ $cur -ge ${#uppercase[@]} ]]; then
        echo "Превышен диапазон символов для $char_set"
        exit 1
      fi
      cur_char="${uppercase[$(( (start + i) % ${#uppercase[@]} ))]}"
    fi

    copy_name="${base_name}_${cur_char}${extension}"
    copy_path="${dir}/${copy_name}"

    cp "$source_file" "$copy_path"
    echo "Создан файл: $copy_path"
  done
}

if [[ $# -ne 4 ]]; then
  echo "Использование: $0 <кол-во копий> <исходный файл> <начальный символ> <директория>"
  exit 1
fi

generate "$1" "$2" "$3" "$4"