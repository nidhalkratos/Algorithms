{
 This sourcecode has been written by Nidhal Abidi
 Contact me at nidhalkratos@gmail.com
}
program merger_sort;

const MAX_RANDOM_INT = 1000;  {Change this to get different number ranges}

uses wincrt;

type tab = array[0..100] of integer;

var t:tab;
    i:integer;

{This procedure merges an array with two sorted halfs, Check wikipedia for how merge sort works}
procedure merge(var t:tab;deb,fin:integer);
var temp_arr : tab;
    left_i,right_i,k,mil:integer;
begin
    k:= deb;
    left_i := deb;
    mil := (deb + fin) div 2;
    right_i := mil + 1;
    while(left_i <= mil) and (right_i <= fin) do
    begin
      if(t[left_i] <= t[right_i]) then
      begin
        temp_arr[k] :=  t[left_i];
        left_i := left_i + 1;
      end
      else
      begin
        temp_arr[k] :=  t[right_i];
        right_i := right_i + 1;
      end;
      k:= k +1;
    end;

    while(left_i <= mil) do
    begin
      temp_arr[k] :=  t[left_i];
      left_i := left_i + 1;
      k:= k +1;
    end;

    while(right_i <= fin) do
    begin
      temp_arr[k] :=  t[right_i];
      right_i := right_i + 1;
      k:= k +1;
    end;

    for k := deb to fin do
    begin
      t[k] := temp_arr[k];
    end;
end;

{This is a recursive function that keeps deviding the array into halfs and then merging halfs to create a bigger sorted array, Check Wikipedia for how merge sort works}
procedure merge_sort(var t:tab;deb,fin:integer);
var mil :integer;
begin
    mil := (deb + fin) div 2;
    if(deb <fin) then
    begin
      merge_sort(t,deb,mil);
      merge_sort(t,mil+1,fin );
      merge(t,deb,fin);
    end;
end;


{This procedure is to fill an array with random integers}
procedure fill_random_array(var arr:tab;deb,fin:integer);
var i : integer;
begin
  randomize;
  for i:= deb to fin do
  begin
    t[i] := random(MAX_RANDOM_INT);
  end;
end;

{This procedure prints the array on the screen}
procedure print_array(arr:tab;deb,fin:integer);
var i : integer;
begin
  for i:= deb to fin do
  begin
    write(t[i], ' ');
  end;
  writeln;
end;

begin
  fill_random_array(t,0,20);    {Fill the array with random values}
  print_array(t,0,20);          {Print the display to see how it was}
  merge_sort(t,0,20);           {Sort the array with merge sort algorithm}
  print_array(t,0,20);          {Print the array once again to see the newly sorted array}

  readln;
end.
