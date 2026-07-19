import subprocess
import os
import sys

def check_soname(file_path, expected_soname):
    try:
        # Use readelf -d to get dynamic section and grep for SONAME
        output = subprocess.check_output(["readelf", "-d", file_path], stderr=subprocess.STDOUT).decode()
        for line in output.splitlines():
            if "SONAME" in line and expected_soname in line:
                print(f"Found expected SONAME: {expected_soname}")
                return True
        print(f"SONAME {expected_soname} not found in output:")
        print(output)
        return False
    except Exception as e:
        print(f"Error checking SONAME: {e}")
        return False

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: test_soname.py <library_path> <expected_soname>")
        sys.exit(1)
    
    lib_path = sys.argv[1]
    expected = sys.argv[2]
    
    if check_soname(lib_path, expected):
        sys.exit(0)
    else:
        sys.exit(1)
