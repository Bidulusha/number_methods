class perfect_table_manager:
    def __init__(self, header, width=10):
        self.__header = header
        self.__width = width
        self._create_perfect_table()

    def __format_value(self, value):
        if isinstance(value, float):
            return f"{value:.4f}"
        elif isinstance(value, int):
            return str(value)
        else:
            return str(value)

    def _create_perfect_table(self):
        for name in self.__header:
            print(f"{str(name):<{self.__width}}|", end='')
        print()
        

        total_width = len(self.__header) * (self.__width + 1)
        print('-' * total_width)

    def add_line(self, line):
        for value in line:
            formatted_value = self.__format_value(value)

            if len(formatted_value) > self.__width:
                formatted_value = formatted_value[:self.__width]
            
            print(f"{formatted_value:<{self.__width}}|", end='')
        print()