def read_pbm(file):
    f = open(file)
    read = f.read() # read is str
    rows = read.split('\n')
    del rows[0] #ignore the first row
    del rows[0]

    pixels = map(lambda x: map(int, x), map(list, rows))

    del pixels[len(pixels) - 1] # get rid of the last array which is empty (how did it even get there?)
    return pixels

def get_dimensions(file):
    f = open(file)
    read = f.read()
    rows = read.split('\n')
    del rows[0]
    dimensions = map(int, rows[0].split(' '))
    width = dimensions[0]
    height = dimensions[1]
    return (width, height)

def fileNameFrom(fstruct, n, f):
    file = fstruct.replace('*N', str(n))
    num = str(f)
    if len(num) == 1:
        num = '0' + num
    file = file.replace('*F', num)
    return file

if __name__ == '__main__':
    fstruct = 'pbms/digit/*N_*F.pbm'
    file = fileNameFrom(fstruct, 1,0)
    print get_dimensions(file)#'pbms/digit/0_00.pbm'