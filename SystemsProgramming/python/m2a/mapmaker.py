import staticmap
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

class mapmaker:
    def __init__(self):
        self.my_map = staticmap.StaticMap(500, 500)
    
    def make_map(self, cent_long, cent_lat, coords_and_colors, outfile):
        for line in coords_and_colors:
            new_marker = staticmap.CircleMarker((line[0], line[1]), line[2], 5)
            self.my_map.add_marker(new_marker)
        center = staticmap.CircleMarker((cent_long, cent_lat), '#000000', 5)
        self.my_map.add_marker(center)
        image = self.my_map.render()
        image.save(outfile)
        my_extents = self.my_map.determine_extent()
        return my_extents

    def add_axes(self, map_extents, plot_title, outfile): 
        map_img = mpimg.imread(outfile)
        imgplot = plt.imshow(map_img, extent=map_extents)
        plt.title(plot_title)
        plt.savefig(outfile)
