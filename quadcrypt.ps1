function TwoEncrypt {
  Write-Host "a : " -NoNewline
  [double]$ra = Read-Host
  Write-Host "b : " -NoNewline
  [double]$rb = Read-Host
  Write-Host "c : " -NoNewline
  [double]$rc = Read-Host
  Write-Host "Input string: " -NoNewline
  $strings = Read-Host
  $output = @()
  
  [double]$a = $ra + $rb
  [double]$b = $rb + $rc
  [double]$c = $rc + $ra
  [double]$fy = [Math]::Pow(($a * $b * $c), 2)
  
  $a = ($fy % ($a + $b) + $a) % ($b + $c) + 1
  $b = ($b % ($b + $c + $a) + $b) % ($c + $a) + 1
  $c = ($fy % ($c + $a) + $c) % ($a + $b) + ($a * $b * $c) % 3
  
  [double]$x = [byte][char]$strings[0]
  [double]$y = $a * [Math]::Pow(($x + $b), 2) + $c
  $output += $y
  
  for ($i = 1; $i -lt $strings.Length; $i++) {
    if ($b -eq 0) { $b = 1 }
    if ($a -eq 0) { $a = 1 }
    if ($c -eq 0) { $c = 1 }
    
    $a = ($y % $b + $a) % ($b + $a) + 1
    $b = ($y % $a + $b) % $c + 1
    $c = ($x % ($c * $a) + $c) % $a + ($a * $b * $c) % 11
    
    $y = $a * [Math]::Pow(([byte][char]$strings[$i] + $b), 2) + $c
    $x = [byte][char]$strings[$i]
    $output += $y
  }
  return $output
}

function TwoDecrypt {
  Write-Host "a : " -NoNewline
  [double]$ra = Read-Host
  Write-Host "b : " -NoNewline
  [double]$rb = Read-Host
  Write-Host "c : " -NoNewline
  [double]$rc = Read-Host
  Write-Host "y : " -NoNewline
  $inputStr = Read-Host
  $ens = $inputStr -split ', ' | ForEach-Object { [double]$_ }
  
  [double]$a = $ra + $rb
  [double]$b = $rb + $rc
  [double]$c = $rc + $ra
  [double]$fy = [Math]::Pow(($a * $b * $c), 2)
  
  $a = ($fy % ($a + $b) + $a) % ($b + $c) + 1
  $b = ($b % ($b + $c + $a) + $b) % ($c + $a) + 1
  $c = ($fy % ($c + $a) + $c) % ($a + $b) + ($a * $b * $c) % 3
  
  foreach ($i in $ens) {
    if ($b -eq 0) { $b = 1 }
    if ($a -eq 0) { $a = 1 }
    if ($c -eq 0) { $c = 1 }
    
    try {
      $x = [int]([Math]::Floor([Math]::Sqrt(($i - $c) / $a) - $b))
      Write-Host ([char]$x) -NoNewline
      $a = ($i % $b + $a) % ($b + $a) + 1
      $b = ($i % $a + $b) % $c + 1
      $c = ($x % ($c * $a) + $c) % $a + ($a * $b * $c) % 11
    }
    catch {
      Write-Error "Error processing value: $i"
    }
  }
  Write-Host ""
}

$encrypted = TwoEncrypt
Write-Host ($encrypted -join ', ')
TwoDecrypt
