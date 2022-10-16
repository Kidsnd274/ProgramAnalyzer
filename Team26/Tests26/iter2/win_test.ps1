$autotester = "..\..\Code37\out\build\x64-Release\src\autotester\autotester.exe"
$source1 = ".\source1.txt"
$source2 = ".\source2.txt"
$source3 = ".\source3.txt"

$queryPrefix1 = ".\source1_"
$queryPrefix2 = ".\source2_"
$queryPrefix3 = ".\source3_"
$querySuffix = "_queries.txt"
$outputPrefix1 = "..\out\source1_"
$outputPrefix2 = "..\out\source2_"
$outputPrefix3 = "..\out\source3_"
$outputSuffix = "_out.xml"

$queries1 = @(
    "calls"
    "modifies"
    "uses"
)

$queries2 = @(
    "multiple"
    "next"
    "pattern"
    "tuples"
    "tuples_attr"
    "with"
    "affect"
    "boolean"
)

$query3 = "affects_loop"


for ($x = 0; $x -lt $queries1.count; $x = $x + 1) {
    $query = $queries1[$x]
    &$autotester $source1 $queryPrefix1$query$querySuffix $outputPrefix1$query$outputSuffix
}

for ($x = 0; $x -lt $queries2.count; $x = $x + 1) {
    $query = $queries2[$x]
    &$autotester $source2 $queryPrefix2$query$querySuffix $outputPrefix2$query$outputSuffix
}

&$autotester $source3 $queryPrefix3$query3$querySuffix $outputPrefix3$query3$outputSuffix
